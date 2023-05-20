package com.ubb.protocol;

import com.ubb.IMainObserver;
import com.ubb.IContestServices;
import com.ubb.exceptions.ContestDataException;
import com.ubb.model.*;
import com.ubb.dto.RaceDTO;
import com.ubb.protocol.request.*;
import com.ubb.protocol.response.*;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.Collection;
import java.util.List;
import java.util.Optional;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class ServicesProxy implements IContestServices {
    private final String host;
    private final int port;
    private IMainObserver client;

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private Socket connection;

    private final BlockingQueue<Response> responseQueue;
    private volatile boolean finished;

    public ServicesProxy(String host, int port) {
        this.host = host;
        this.port = port;
        responseQueue = new LinkedBlockingQueue<>();
    }

    @Override
    public User login(String username, String password, IMainObserver client) throws ContestDataException {
        initializeConnection();
        sendRequest(new LoginRequest(username, password));
        Response response = readResponse();
        if (response instanceof OKResponse) {
            this.client = client;
            return ((OKResponse) response).getUser();
        }
        if (response instanceof ErrorResponse) {
            closeConnection();
            throw new ContestDataException(((ErrorResponse) response).getErrorMessage());
        }
        return null;
    }

    @Override
    public void logout(User user, IMainObserver client) throws ContestDataException {
        sendRequest(new LogoutRequest(user));
        Response response = readResponse();
        closeConnection();
        if (response instanceof ErrorResponse){
            throw new ContestDataException(((ErrorResponse) response).getErrorMessage());
        }
    }

    @Override
    public Collection<Participant> getParticipantsByTeam(Long teamID) throws ContestDataException {
        sendRequest(new GetParticipantsByTeamRequest(teamID));
        Response response = readResponse();
        if (response instanceof ErrorResponse) {
            throw new ContestDataException(((ErrorResponse) response).getErrorMessage());
        }
        GetParticipantsByTeamResponse participantsResponse = (GetParticipantsByTeamResponse) response;
        return participantsResponse.getParticipants();
    }

    @Override
    public Optional<Participant> getParticipantByData(Participant participant) throws ContestDataException {
        sendRequest(new GetParticipantByDataRequest(participant));
        Response response = readResponse();
        if (response instanceof ErrorResponse) {
            throw new ContestDataException(((ErrorResponse) response).getErrorMessage());
        }
        ParticipantResponse participantResponse = (ParticipantResponse) response;
        return Optional.of(participantResponse.getParticipant());
    }

    @Override
    public Optional<Race> getRaceByName(String name) throws ContestDataException {
        sendRequest(new GetRaceByNameRequest(name));
        Response response = readResponse();
        if (response instanceof ErrorResponse) {
            throw new ContestDataException(((ErrorResponse) response).getErrorMessage());
        }
        RaceByNameResponse raceResponse = (RaceByNameResponse) response;
        return Optional.of(raceResponse.getRace());
    }

    @Override
    public Collection<RaceEntry> getEntriesByRace(Long raceID) throws ContestDataException {
        sendRequest(new GetEntriesByRaceRequest(raceID));
        Response response = readResponse();
        if (response instanceof ErrorResponse) {
            throw new ContestDataException(((ErrorResponse) response).getErrorMessage());
        }
        EntriesByRaceResponse entriesResponse = (EntriesByRaceResponse) response;
        return entriesResponse.getEntries();
    }

    @Override
    public Collection<Race> getRacesByEngineCapacity(Integer engineCapacity) throws ContestDataException {
        sendRequest(new GetRacesByEngineCapacityRequest(engineCapacity));
        Response response = readResponse();
        if (response instanceof ErrorResponse) {
            throw new ContestDataException(((ErrorResponse) response).getErrorMessage());
        }
        RacesByCapacityResponse racesResponse = (RacesByCapacityResponse) response;
        return racesResponse.getRaces();
    }

    @Override
    public Collection<RaceDTO> getRacesWithParticipantCount() throws ContestDataException {
        sendRequest(new GetRacesWithParticipantCountRequest());
        Response response = readResponse();
        if (response instanceof ErrorResponse) {
            throw new ContestDataException(((ErrorResponse) response).getErrorMessage());
        }
        RacesWithParticipantsResponse racesResponse = (RacesWithParticipantsResponse) response;
        return racesResponse.getRacesDTO();
    }

    @Override
    public void saveRaceEntries(List<RaceEntry> newEntities) throws ContestDataException {
        sendRequest(new CreateRaceEntriesRequest(newEntities));
    }

    @Override
    public Collection<Race> getRacesWhereNotRegisteredAndEngineCapacity(Long participantID, Integer engineCapacity) throws ContestDataException {
        sendRequest(new GetUnregisteredRacesRequest(participantID, engineCapacity));
        Response response = readResponse();
        if (response instanceof ErrorResponse) {
            throw new ContestDataException(((ErrorResponse) response).getErrorMessage());
        }
        RacesByCapacityResponse racesResponse = (RacesByCapacityResponse) response;
        return racesResponse.getRaces();
    }

    @Override
    public Optional<Team> getTeamByName(String teamName) throws ContestDataException {
        sendRequest(new GetTeamByNameRequest(teamName));
        Response response = readResponse();
        if (response instanceof ErrorResponse) {
            throw new ContestDataException(((ErrorResponse) response).getErrorMessage());
        }
        TeamResponse teamResponse = (TeamResponse) response;
        return Optional.of(teamResponse.getTeam());
    }

    @Override
    public void saveParticipant(Participant newEntity) throws ContestDataException {
        sendRequest(new CreateParticipantRequest(newEntity));
    }

    @Override
    public void saveRace(Race newEntity) throws ContestDataException {
        sendRequest(new CreateRaceRequest(newEntity));
    }

    @Override
    public Collection<Team> findAllTeams() throws ContestDataException {
        sendRequest(new GetTeamsRequest());
        Response response = readResponse();
        if (response instanceof ErrorResponse) {
            throw new ContestDataException(((ErrorResponse) response).getErrorMessage());
        }
        AllTeamsResponse teamsResponse = (AllTeamsResponse) response;
        return teamsResponse.getTeams();
    }

    @Override
    public Collection<Participant> findAllParticipants() throws ContestDataException {
        sendRequest(new GetParticipantsRequest());
        Response response = readResponse();
        if (response instanceof ErrorResponse) {
            throw new ContestDataException(((ErrorResponse) response).getErrorMessage());
        }
        AllParticipantsResponse participantsResponse = (AllParticipantsResponse) response;
        return participantsResponse.getParticipants();
    }

    private void initializeConnection() throws ContestDataException {
        try {
            connection = new Socket(host, port);
            output = new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input = new ObjectInputStream(connection.getInputStream());
            finished = false;
            startResponseReader();
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    private void closeConnection() {
        finished = true;
        try {
            input.close();
            output.close();
            connection.close();
            client = null;
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    private void startResponseReader() {
        Thread responseReader = new Thread(new ReaderThread());
        responseReader.start();
    }

    private void handleUpdate(UpdateResponse update) {
        try {
            if (update instanceof final NewParticipantResponse participantResponse) {
                client.participantAdded(participantResponse.getParticipant());
            }

            if (update instanceof final NewRaceResponse raceResponse) {
                client.raceAdded(raceResponse.getRaceDTO());
            }

            if (update instanceof final UpdatedRacesResponse racesResponse) {
                client.raceEntriesAdded(racesResponse.getRacesDTO());
            }
        } catch (ContestDataException e) {
            e.printStackTrace();
        }
    }

    private void sendRequest(Request request) throws ContestDataException {
        try {
            output.writeObject(request);
            output.flush();
        } catch (IOException ioException) {
            throw new ContestDataException("Error sending object: " + ioException);
        }
    }

    private Response readResponse() throws ContestDataException {
        Response response;
        try {
            response = responseQueue.take();
        } catch (InterruptedException interruptedException) {
            throw new ContestDataException("Error reading response: " + interruptedException);
        }
        return response;
    }

    private class ReaderThread implements Runnable {
        public void run() {
            while (!finished) {
                try {
                    Object response = input.readObject();
                    System.out.println("response received " + response);
                    if (response instanceof UpdateResponse) {
                        handleUpdate((UpdateResponse) response);
                    } else {
                        try {
                            responseQueue.put((Response) response);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                } catch (IOException | ClassNotFoundException exception) {
                    System.out.println("reading error: " + exception);
                }
            }
        }
    }

}
