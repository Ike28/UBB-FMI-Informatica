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
import java.util.Collection;
import java.util.List;
import java.util.Optional;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class ProtobufServicesProxy implements IContestServices {
    private final String host;
    private final int port;
    private IMainObserver client;
    private InputStream inputStream;
    private OutputStream outputStream;
    private Socket connection;
    private final BlockingQueue<BikeContestProtocol.BikeContestResponse> responses;
    private volatile boolean finished;

    public ProtobufServicesProxy (String host, int port) {
        this.host = host;
        this.port = port;
        this.responses = new LinkedBlockingQueue<>();
    }

    @Override
    public User login(String username, String passwordToken, IMainObserver client) throws ContestDataException {
        initialiseConnection();
        BikeContestProtocol.BikeContestRequest request
                = ProtocolBuilderUtils.createLoginRequest(username, passwordToken);
        sendRequest(request);

        BikeContestProtocol.BikeContestResponse response = readResponse();
        if (response.getType() == BikeContestProtocol.BikeContestResponse.Type.Error) {
            closeConnection();
            throw new ContestDataException(ProtocolBuilderUtils.getErrorMessage(response));
        } else if (response.getType() == BikeContestProtocol.BikeContestResponse.Type.Ok) {
            this.client = client;
            return ProtocolBuilderUtils.getUser(response);
        } else {
            throw new ContestDataException("Authentication failed : expected OK response, got " + response.getType());
        }
    }

    @Override
    public void logout(User user, IMainObserver client) throws ContestDataException {
        BikeContestProtocol.BikeContestRequest request = ProtocolBuilderUtils.createLogoutRequest(user);
        sendRequest(request);

        BikeContestProtocol.BikeContestResponse response = readResponse();
        closeConnection();

        if (response.getType() == BikeContestProtocol.BikeContestResponse.Type.Error) {
            throw new ContestDataException(ProtocolBuilderUtils.getErrorMessage(response));
        }
    }

    @Override
    public Collection<Participant> getParticipantsByTeam(Long teamID) throws ContestDataException {
        BikeContestProtocol.BikeContestRequest request
                = ProtocolBuilderUtils.createGetParticipantsByTeamRequest(teamID);
        sendRequest(request);

        BikeContestProtocol.BikeContestResponse response = readResponse();
        if (response.getType() == BikeContestProtocol.BikeContestResponse.Type.Error) {
            throw new ContestDataException(ProtocolBuilderUtils.getErrorMessage(response));
        }
        return ProtocolBuilderUtils.getParticipants(response);
    }

    @Override
    public Optional<Participant> getParticipantByData(Participant participant) throws ContestDataException {
        BikeContestProtocol.BikeContestRequest request
                = ProtocolBuilderUtils.createGetParticipantByDataRequest(participant);
        sendRequest(request);

        BikeContestProtocol.BikeContestResponse response = readResponse();
        if (response.getType() == BikeContestProtocol.BikeContestResponse.Type.Error) {
            throw new ContestDataException(ProtocolBuilderUtils.getErrorMessage(response));
        }
        return Optional.of(ProtocolBuilderUtils.getParticipant(response));
    }

    @Override
    public Optional<Race> getRaceByName(String name) throws ContestDataException {
        BikeContestProtocol.BikeContestRequest request
                = ProtocolBuilderUtils.createGetRaceByNameRequest(name);
        sendRequest(request);

        BikeContestProtocol.BikeContestResponse response = readResponse();
        if (response.getType() == BikeContestProtocol.BikeContestResponse.Type.Error) {
            throw new ContestDataException(ProtocolBuilderUtils.getErrorMessage(response));
        }
        return Optional.of(ProtocolBuilderUtils.getRace(response));
    }

    @Override
    public Collection<RaceEntry> getEntriesByRace(Long raceID) throws ContestDataException {
        BikeContestProtocol.BikeContestRequest request = ProtocolBuilderUtils.createGetEntriesByRaceRequest(raceID);
        sendRequest(request);

        BikeContestProtocol.BikeContestResponse response = readResponse();
        if (response.getType() == BikeContestProtocol.BikeContestResponse.Type.Error) {
            throw new ContestDataException(ProtocolBuilderUtils.getErrorMessage(response));
        }
        return ProtocolBuilderUtils.getRaceEntries(response);
    }

    @Override
    public Collection<Race> getRacesByEngineCapacity(Integer engineCapacity) throws ContestDataException {
        BikeContestProtocol.BikeContestRequest request
                = ProtocolBuilderUtils.createGetRacesByEngineCapacityRequest(engineCapacity);
        sendRequest(request);

        BikeContestProtocol.BikeContestResponse response = readResponse();
        if (response.getType() == BikeContestProtocol.BikeContestResponse.Type.Error) {
            throw new ContestDataException(ProtocolBuilderUtils.getErrorMessage(response));
        }
        return ProtocolBuilderUtils.getRaces(response);
    }

    @Override
    public Collection<RaceDTO> getRacesWithParticipantCount() throws ContestDataException {
        BikeContestProtocol.BikeContestRequest request
                = ProtocolBuilderUtils.createGetRacesWithParticipantCount();
        sendRequest(request);

        BikeContestProtocol.BikeContestResponse response = readResponse();
        if (response.getType() == BikeContestProtocol.BikeContestResponse.Type.Error) {
            throw new ContestDataException(ProtocolBuilderUtils.getErrorMessage(response));
        }
        return ProtocolBuilderUtils.getRaceDTOs(response);
    }

    @Override
    public void saveRaceEntries(List<RaceEntry> newEntities) throws ContestDataException {
        BikeContestProtocol.BikeContestRequest request
                = ProtocolBuilderUtils.createNewRaceEntriesRequest(newEntities);
        sendRequest(request);
    }

    @Override
    public Collection<Race> getRacesWhereNotRegisteredAndEngineCapacity(Long participantID, Integer engineCapacity) throws ContestDataException {
        BikeContestProtocol.BikeContestRequest request
                = ProtocolBuilderUtils.createGetUnregisteredRacesRequest(participantID, engineCapacity);
        sendRequest(request);

        BikeContestProtocol.BikeContestResponse response = readResponse();
        if (response.getType() == BikeContestProtocol.BikeContestResponse.Type.Error) {
            throw new ContestDataException(ProtocolBuilderUtils.getErrorMessage(response));
        }
        return ProtocolBuilderUtils.getRaces(response);
    }

    @Override
    public Optional<Team> getTeamByName(String teamName) throws ContestDataException {
        BikeContestProtocol.BikeContestRequest request
                = ProtocolBuilderUtils.createGetTeamByNameRequest(teamName);
        sendRequest(request);

        BikeContestProtocol.BikeContestResponse response = readResponse();
        if (response.getType() == BikeContestProtocol.BikeContestResponse.Type.Error) {
            throw new ContestDataException(ProtocolBuilderUtils.getErrorMessage(response));
        }
        return Optional.of(ProtocolBuilderUtils.getTeam(response));
    }

    @Override
    public void saveParticipant(Participant newEntity) throws ContestDataException {
        BikeContestProtocol.BikeContestRequest request
                = ProtocolBuilderUtils.createNewParticipantRequest(newEntity);
        sendRequest(request);
    }

    @Override
    public void saveRace(Race newEntity) throws ContestDataException {
        BikeContestProtocol.BikeContestRequest request
                = ProtocolBuilderUtils.createNewRaceRequest(newEntity);
        sendRequest(request);
    }

    @Override
    public Collection<Team> findAllTeams() throws ContestDataException {
        BikeContestProtocol.BikeContestRequest request = ProtocolBuilderUtils.createGetTeamsRequest();
        sendRequest(request);

        BikeContestProtocol.BikeContestResponse response = readResponse();
        if (response.getType() == BikeContestProtocol.BikeContestResponse.Type.Error) {
            throw new ContestDataException(ProtocolBuilderUtils.getErrorMessage(response));
        }
        return ProtocolBuilderUtils.getTeams(response);
    }

    @Override
    public Collection<Participant> findAllParticipants() throws ContestDataException {
        BikeContestProtocol.BikeContestRequest request = ProtocolBuilderUtils.createGetParticipantsRequest();
        sendRequest(request);

        BikeContestProtocol.BikeContestResponse response = readResponse();
        if (response.getType() == BikeContestProtocol.BikeContestResponse.Type.Error) {
            throw new ContestDataException(ProtocolBuilderUtils.getErrorMessage(response));
        }
        return ProtocolBuilderUtils.getParticipants(response);
    }

    private void sendRequest(BikeContestProtocol.BikeContestRequest request) throws ContestDataException {
        try {
            System.out.println("Sending request..." + request);
            request.writeDelimitedTo(outputStream);
            outputStream.flush();
            System.out.println("Request sent.");
        } catch (IOException ioException) {
            throw new ContestDataException("Error while sending request object: " + ioException);
        }
    }

    private BikeContestProtocol.BikeContestResponse readResponse() throws ContestDataException {
        BikeContestProtocol.BikeContestResponse response = null;

        try {
            response = responses.take();
        } catch (InterruptedException interruptedException) {
            throw new ContestDataException("Error while reading response object: " + interruptedException);
        }
        return response;
    }

    private boolean isUpdateResponse(BikeContestProtocol.BikeContestResponse response) {
        return response.getType() == BikeContestProtocol.BikeContestResponse.Type.NewParticipant
                || response.getType() == BikeContestProtocol.BikeContestResponse.Type.NewRace
                || response.getType() == BikeContestProtocol.BikeContestResponse.Type.NewTeam
                || response.getType() == BikeContestProtocol.BikeContestResponse.Type.UpdatedRaces;
    }

    private void handleUpdate(BikeContestProtocol.BikeContestResponse response) throws ContestDataException {
        switch (response.getType()) {
            case NewParticipant -> client.participantAdded(ProtocolBuilderUtils.getParticipant(response));

            case NewRace -> client.raceAdded(ProtocolBuilderUtils.getRaceDto(response));

            case UpdatedRaces -> client.raceEntriesAdded(ProtocolBuilderUtils.getRaceDTOs(response));
        }
    }

    private void initialiseConnection() {
        try {
            connection = new Socket(host, port);
            outputStream = connection.getOutputStream();
            inputStream = connection.getInputStream();
            finished = false;
            startReader();
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    private void closeConnection() {
        finished = true;
        try {
            inputStream.close();
            outputStream.close();
            connection.close();
            client = null;
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    private void startReader() {
        Thread threadWorker = new Thread(new ReaderThread());
        threadWorker.start();
    }

    private class ReaderThread implements Runnable {
        public void run() {
            while (!finished) {
                try {
                    BikeContestProtocol.BikeContestResponse response
                            = BikeContestProtocol.BikeContestResponse.parseDelimitedFrom(inputStream);
                    System.out.println("Response received: " + response);

                    if (isUpdateResponse(response)) {
                        handleUpdate(response);
                    } else {
                        try {
                            responses.put(response);
                        } catch (InterruptedException interruptedException) {
                            interruptedException.printStackTrace();
                        }
                    }
                } catch (IOException ioException) {
                    System.out.println("Error while reading: " + ioException.getMessage());
                } catch (ContestDataException contestDataException) {
                    System.out.println(contestDataException.getMessage());
                }
            }
        }
    }
}
