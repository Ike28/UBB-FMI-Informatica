package com.ubb.protocolbuffers;

import com.ubb.IContestServices;
import com.ubb.IMainObserver;
import com.ubb.dto.RaceDTO;
import com.ubb.exceptions.ContestDataException;
import com.ubb.model.*;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class ProtocolBufferWorker implements Runnable, IMainObserver {
    private final IContestServices server;
    private final Socket connection;
    private InputStream inputStream;
    private OutputStream outputStream;
    private volatile boolean connected;

    public ProtocolBufferWorker(IContestServices server, Socket connection) {
        this.server = server;
        this.connection = connection;
        try {
            outputStream = connection.getOutputStream();
            inputStream = connection.getInputStream();
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    @Override
    public void raceAdded(RaceDTO race) throws ContestDataException {
        try {
            BikeContestProtocol.BikeContestResponse response = ProtocolBuilderUtils.createNewRaceResponse(race);
            System.out.println("Race added: " + race);
            sendResponse(response);
        } catch (IOException ioException) {
            throw new ContestDataException("Error while sending response object: " + ioException);
        }
    }

    @Override
    public void participantAdded(Participant participant) throws ContestDataException {
        try {
            BikeContestProtocol.BikeContestResponse response
                    = ProtocolBuilderUtils.createNewParticipantResponse(participant);
            System.out.println("Participant added: " + participant);
            sendResponse(response);
        } catch (IOException ioException) {
            throw new ContestDataException("Error while sending response object: " + ioException);
        }
    }

    @Override
    public void raceEntriesAdded(List<RaceDTO> races) throws ContestDataException {
        try {
            BikeContestProtocol.BikeContestResponse response
                    = ProtocolBuilderUtils.createUpdatedRacesResponse(races);
            System.out.println("Race entries added: " + races);
            sendResponse(response);
        } catch (IOException ioException) {
            throw new ContestDataException("Error while sending response object: " + ioException);
        }
    }

    @Override
    public void run() {
        while (connected) {
            try {
                System.out.println("Waiting for requests...");
                BikeContestProtocol.BikeContestRequest request
                        = BikeContestProtocol.BikeContestRequest.parseDelimitedFrom(inputStream);
                System.out.println("Request received: " + request);

                BikeContestProtocol.BikeContestResponse response = handleRequest(request);
                if (response != null) {
                    sendResponse(response);
                }
            } catch (IOException ioException) {
                ioException.printStackTrace();
            }

            try {
                Thread.sleep(1000);
            } catch (InterruptedException interruptedException) {
                interruptedException.printStackTrace();
            }
        }
    }

    private BikeContestProtocol.BikeContestResponse handleRequest(BikeContestProtocol.BikeContestRequest request) {
        BikeContestProtocol.BikeContestResponse response = null;

        switch (request.getType()) {
            case Login -> {
                System.out.println("> handling login request...");
                final String username = ProtocolBuilderUtils.getUsername(request);
                final String passwordToken = ProtocolBuilderUtils.getPasswordToken(request);

                try {
                    final User loggedUser = server.login(username, passwordToken, this);
                    return ProtocolBuilderUtils.createOkResponse(loggedUser);
                } catch (ContestDataException contestDataException) {
                    connected = false;
                    return ProtocolBuilderUtils.createErrorResponse(contestDataException.getMessage());
                }
            }

            case Logout -> {
                System.out.println("> handling logout request");
                final User user = ProtocolBuilderUtils.getUser(request);

                try {
                    server.logout(user, this);
                    connected = false;
                    return ProtocolBuilderUtils.createOkResponse();
                } catch (ContestDataException contestDataException) {
                    return ProtocolBuilderUtils.createErrorResponse(contestDataException.getMessage());
                }
            }

            case CreateRace -> {
                System.out.println("> handling create race request...");
                final Race race = ProtocolBuilderUtils.getRaceDto(request);

                try {
                    server.saveRace(race);
                    final Optional<Race> createdRace = server.getRaceByName(race.getName());
                    if (createdRace.isEmpty()) {
                        throw new ContestDataException("Race could not be created.");
                    }
                    List<RaceEntry> raceEntries = new ArrayList<>(server.getEntriesByRace(createdRace.get().getId()));

                    return ProtocolBuilderUtils.createNewRaceResponse(
                            new RaceDTO(race.getName(), race.getEngineCapacity(), raceEntries.size()));
                } catch (ContestDataException contestDataException) {
                    return ProtocolBuilderUtils.createErrorResponse(contestDataException.getMessage());
                }
            }

            case CreateParticipant -> {
                System.out.println("> handling create participant request");
                final Participant participant = ProtocolBuilderUtils.getParticipant(request);

                try {
                    server.saveParticipant(participant);
                    final Optional<Participant> savedParticipant = server.getParticipantByData(participant);
                    if (savedParticipant.isEmpty()) {
                        throw new ContestDataException("Participant could not be created.");
                    }
                    return ProtocolBuilderUtils.createNewParticipantResponse(savedParticipant.get());
                } catch (ContestDataException contestDataException) {
                    return ProtocolBuilderUtils.createErrorResponse(contestDataException.getMessage());
                }
            }

            case CreateRaceEntries -> {
                System.out.println("> handling create race entries request");
                final List<RaceEntry> raceEntries = ProtocolBuilderUtils.getRaceEntries(request);

                try {
                    server.saveRaceEntries(raceEntries);

                    return ProtocolBuilderUtils.createUpdatedRacesResponse(
                            server.getRacesWithParticipantCount().stream().toList());
                } catch (ContestDataException contestDataException) {
                    return ProtocolBuilderUtils.createErrorResponse(contestDataException.getMessage());
                }
            }

            case GetEntriesByRace -> {
                System.out.println("> handling get entries by race request");
                final Long raceId = ProtocolBuilderUtils.getRaceId(request);

                try {
                    List<RaceEntry> raceEntries = server.getEntriesByRace(raceId).stream().toList();

                    return ProtocolBuilderUtils.createEntriesByRaceResponse(raceEntries);
                } catch (ContestDataException contestDataException) {
                    return ProtocolBuilderUtils.createErrorResponse(contestDataException.getMessage());
                }
            }

            case GetParticipantByData -> {
                System.out.println("> handling get participant by data request");
                final Participant participant = ProtocolBuilderUtils.getParticipant(request);

                try {
                    Optional<Participant> found = server.getParticipantByData(participant);
                    if (found.isEmpty()) {
                        throw new ContestDataException("Participant could not be found.");
                    }
                    return ProtocolBuilderUtils.createParticipantResponse(found.get());
                } catch (ContestDataException contestDataException) {
                    return ProtocolBuilderUtils.createErrorResponse(contestDataException.getMessage());
                }
            }

            case GetParticipantsByTeam -> {
                System.out.println("> handling get participants by team request");
                final Long teamId = ProtocolBuilderUtils.getTeamId(request);

                try {
                    List<Participant> participants = server.getParticipantsByTeam(teamId).stream().toList();

                    return ProtocolBuilderUtils.createParticipantsByTeamResponse(participants);
                } catch (ContestDataException contestDataException) {
                    return ProtocolBuilderUtils.createErrorResponse(contestDataException.getMessage());
                }
            }

            case GetParticipants -> {
                System.out.println("> handling get participants request");

                try {
                    List<Participant> participants = server.findAllParticipants().stream().toList();

                    return ProtocolBuilderUtils.createAllParticipantsResponse(participants);
                } catch (ContestDataException contestDataException) {
                    return ProtocolBuilderUtils.createErrorResponse(contestDataException.getMessage());
                }
            }

            case GetRaceByName -> {
                System.out.println("> handling get race by name request");
                final String raceName = ProtocolBuilderUtils.getRaceName(request);

                try {
                    Optional<Race> found = server.getRaceByName(raceName);
                    if (found.isEmpty()) {
                        throw new ContestDataException("Participant could not be found.");
                    }

                    return ProtocolBuilderUtils.createGetRaceByNameResponse(found.get());
                } catch (ContestDataException contestDataException) {
                    return ProtocolBuilderUtils.createErrorResponse(contestDataException.getMessage());
                }
            }

            case GetRacesByEngineCapacity -> {
                System.out.println("> handling get races by capacity request");
                final Integer capacity = ProtocolBuilderUtils.getEngineCapacity(request);

                try {
                    List<Race> races = server.getRacesByEngineCapacity(capacity).stream().toList();

                    return ProtocolBuilderUtils.createGetRacesByCapacityResponse(races);
                } catch (ContestDataException contestDataException) {
                    return ProtocolBuilderUtils.createErrorResponse(contestDataException.getMessage());
                }
            }

            case GetRacesWithParticipantCount -> {
                System.out.println("> handling get races with participants request");

                try {
                    List<RaceDTO> races = server.getRacesWithParticipantCount().stream().toList();

                    return ProtocolBuilderUtils.createGetRacesWithParticipantsResponse(races);
                } catch (ContestDataException contestDataException) {
                    return ProtocolBuilderUtils.createErrorResponse(contestDataException.getMessage());
                }
            }

            case GetTeamByName -> {
                System.out.println("> handling get team by name request");
                final String teamName = ProtocolBuilderUtils.getTeamName(request);

                try {
                    Optional<Team> found = server.getTeamByName(teamName);
                    if (found.isEmpty()) {
                        throw new ContestDataException("Participant could not be found.");
                    }

                    return ProtocolBuilderUtils.createGetTeamResponse(found.get());
                } catch (ContestDataException contestDataException) {
                    return ProtocolBuilderUtils.createErrorResponse(contestDataException.getMessage());
                }
            }

            case GetTeams -> {
                System.out.println("> handling get teams request");

                try {
                    List<Team> teams = server.findAllTeams().stream().toList();

                    return ProtocolBuilderUtils.createAllTeamsResponse(teams);
                } catch (ContestDataException contestDataException) {
                    return ProtocolBuilderUtils.createErrorResponse(contestDataException.getMessage());
                }
            }

            case GetUnregisteredRaces -> {
                System.out.println("> handling get unregistered races request");
                final Long participantId = ProtocolBuilderUtils.getParticipantId(request);
                final Integer capacity = ProtocolBuilderUtils.getEngineCapacity(request);

                try {
                    List<Race> races
                            = server.getRacesWhereNotRegisteredAndEngineCapacity(participantId, capacity)
                            .stream().toList();

                    return ProtocolBuilderUtils.createGetRacesByCapacityResponse(races);
                } catch (ContestDataException contestDataException) {
                    return ProtocolBuilderUtils.createErrorResponse(contestDataException.getMessage());
                }
            }
        }

        return null;
    }

    private void sendResponse(BikeContestProtocol.BikeContestResponse response) throws IOException {
        System.out.println("Sending response: " + response);
        response.writeDelimitedTo(outputStream);
        outputStream.flush();
    }
}
