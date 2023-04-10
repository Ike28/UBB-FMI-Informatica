package com.ubb.protocol;

import com.ubb.IMainObserver;
import com.ubb.IContestServices;
import com.ubb.exceptions.ContestDataException;
import com.ubb.model.Participant;
import com.ubb.model.User;
import com.ubb.dto.RaceDTO;
import com.ubb.protocol.request.*;
import com.ubb.protocol.response.*;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.List;

public class ClientWorker implements Runnable, IMainObserver {
    private IContestServices server;
    private Socket connection;

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private volatile boolean connected;

    public ClientWorker(IContestServices server, Socket connection) {
        this.server = server;
        this.connection = connection;
        try {
            output = new ObjectOutputStream(connection.getOutputStream());
            output.flush();

            input = new ObjectInputStream(connection.getInputStream());
            connected = true;
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    @Override
    public void raceAdded(RaceDTO race) throws ContestDataException {
        try {
            sendResponse(new NewRaceResponse(race));
        } catch (IOException ioException) {
            throw new ContestDataException("Sending error: " + ioException.getMessage());
        }
    }

    @Override
    public void participantAdded(Participant participant) throws ContestDataException {
        try {
            sendResponse(new NewParticipantResponse(participant));
        } catch (IOException ioException) {
            throw new ContestDataException("Sending error: " + ioException.getMessage());
        }
    }

    @Override
    public void raceEntriesAdded(List<RaceDTO> races) throws ContestDataException {
        try {
            sendResponse(new UpdatedRacesResponse(races));
        } catch (IOException ioException) {
            throw new ContestDataException("Sending error: " + ioException.getMessage());
        }
    }

    @Override
    public void run() {
        while (connected) {
            try {
                Object request = input.readObject();
                Response response = handleRequest((Request) request);
                if (response != null) {
                    sendResponse(response);
                }
            } catch (IOException | ClassNotFoundException ioException) {
                ioException.printStackTrace();
            }

            try {
                Thread.sleep(1000);
            } catch (InterruptedException interruptedException) {
                interruptedException.printStackTrace();
            }
        }
        try {
            input.close();
            output.close();
            connection.close();
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    private void sendResponse(Response response) throws IOException {
        System.out.println("sending response " + response);
        synchronized (output) {
            output.writeObject(response);
            output.flush();
        }
    }

    private Response handleRequest(Request request) {
        if (request instanceof LoginRequest loginRequest) {
            System.out.println("Login request...");
            String username = loginRequest.getUsername();
            String token = loginRequest.getToken();
            try {
                User user = server.login(username, token, this);
                return new OKResponse(user);
            } catch (ContestDataException racesException) {
                return new ErrorResponse(racesException.getMessage());
            }
        }

        if (request instanceof LogoutRequest logoutRequest) {
            System.out.println("Logout request");
            User user = logoutRequest.getUser();
            try {
                server.logout(user, this);
                connected=false;
                return new OKResponse(null);

            } catch (ContestDataException racesException) {
                return new ErrorResponse(racesException.getMessage());
            }
        }

        if (request instanceof CreateParticipantRequest createParticipantRequest) {
            System.out.println("Create participant request");
            Participant participant = createParticipantRequest.getParticipant();
            try {
                server.saveParticipant(participant);
                return new NewParticipantResponse(participant);
            } catch (ContestDataException racesException) {
                return new ErrorResponse(racesException.getMessage());
            }
        }

        if (request instanceof CreateRaceEntriesRequest raceEntriesRequest) {
            System.out.println("Create race entries request");
            try {
                server.saveRaceEntries(raceEntriesRequest.getRaceEntries());
                return new UpdatedRacesResponse(server.getRacesWithParticipantCount().stream().toList());
            } catch (ContestDataException racesException) {
                return new ErrorResponse(racesException.getMessage());
            }
        }

        if (request instanceof CreateRaceRequest createRaceRequest) {
            System.out.println("Create race request");
            try {
                server.saveRace(createRaceRequest.getRace());
                return new NewRaceResponse(new RaceDTO(createRaceRequest.getRace().getName(),
                        createRaceRequest.getRace().getEngineCapacity(),
                        server.getEntriesByRace(createRaceRequest.getRace().getID()).size()));
            } catch (ContestDataException racesException) {
                return new ErrorResponse(racesException.getMessage());
            }
        }

        if (request instanceof GetEntriesByRaceRequest getEntriesByRaceRequest) {
            System.out.println("Get entries by race request");
            try {
                return new EntriesByRaceResponse(server.getEntriesByRace(getEntriesByRaceRequest.getRaceID()));
            } catch (ContestDataException racesException) {
                return new ErrorResponse(racesException.getMessage());
            }
        }

        if (request instanceof GetParticipantByDataRequest participantByDataRequest) {
            System.out.println("Get participant request");
            try {
                return new NewParticipantResponse(server.getParticipantByData(
                        participantByDataRequest.getParticipant()).get());
            } catch (ContestDataException racesException) {
                return new ErrorResponse(racesException.getMessage());
            }
        }

        if (request instanceof GetParticipantsByTeamRequest participantsByTeamRequest) {
            System.out.println("Get participants by team request");
            try {
                return new GetParticipantsByTeamResponse(server.getParticipantsByTeam(
                        participantsByTeamRequest.getTeamID()));
            } catch (ContestDataException racesException) {
                return new ErrorResponse(racesException.getMessage());
            }
        }

        if (request instanceof GetRaceByNameRequest raceByNameRequest) {
            System.out.println("Get race request");
            try {
                return new RaceByNameResponse(server.getRaceByName(raceByNameRequest.getRaceName()).get());
            } catch (ContestDataException racesException) {
                return new ErrorResponse(racesException.getMessage());
            }
        }

        if (request instanceof GetRacesByEngineCapacityRequest racesByEngineCapacityRequest) {
            System.out.println("Get races by capacity request");
            try {
                return new RacesByCapacityResponse(server.getRacesByEngineCapacity(
                        racesByEngineCapacityRequest.getEngineCapacity()));
            } catch (ContestDataException racesException) {
                return new ErrorResponse(racesException.getMessage());
            }
        }

        if (request instanceof GetRacesWithParticipantCountRequest) {
            System.out.println("Get races request");
            try {
                return new RacesWithParticipantsResponse(server.getRacesWithParticipantCount());
            } catch (ContestDataException racesException) {
                return new ErrorResponse(racesException.getMessage());
            }
        }

        if (request instanceof GetTeamByNameRequest teamByNameRequest) {
            System.out.println("Get team request");
            try {
                return new TeamResponse(server.getTeamByName(teamByNameRequest.getName()).get());
            } catch (ContestDataException racesException) {
                return new ErrorResponse(racesException.getMessage());
            }
        }

        if (request instanceof GetUnregisteredRacesRequest unregisteredRacesRequest) {
            System.out.println("Get unregistered races request");
            try {
                return new RacesByCapacityResponse(server.getRacesWhereNotRegisteredAndEngineCapacity(
                        unregisteredRacesRequest.getParticipantID(), unregisteredRacesRequest.getEngineCapacity()));
            } catch (ContestDataException racesException) {
                return new ErrorResponse(racesException.getMessage());
            }
        }

        if (request instanceof GetTeamsRequest) {
            System.out.println("Get teams request");
            try {
                return new AllTeamsResponse(server.findAllTeams());
            } catch (ContestDataException racesException) {
                return new ErrorResponse(racesException.getMessage());
            }
        }

        if (request instanceof GetParticipantsRequest) {
            System.out.println("Get participants request");
            try {
                return new AllParticipantsResponse(server.findAllParticipants());
            } catch (ContestDataException racesException) {
                return new ErrorResponse(racesException.getMessage());
            }
        }

        return null;
    }
}
