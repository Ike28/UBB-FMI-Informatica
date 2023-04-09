package com.ubb.protocol;

import com.ubb.IMainObserver;
import com.ubb.IContestServices;
import com.ubb.exceptions.RacesException;
import com.ubb.model.Participant;
import com.ubb.model.User;
import com.ubb.model.data.RaceDTO;
import com.ubb.protocol.request.LoginRequest;
import com.ubb.protocol.request.LogoutRequest;
import com.ubb.protocol.request.Request;
import com.ubb.protocol.response.ErrorResponse;
import com.ubb.protocol.response.OKResponse;
import com.ubb.protocol.response.Response;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

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
    public void raceAdded(RaceDTO race) {

    }

    @Override
    public void participantAdded(Participant participant) {

    }

    @Override
    public void raceEntriesAdded() {

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
        Response response = null;
        if (request instanceof LoginRequest loginRequest) {
            System.out.println("Login request...");
            String username = loginRequest.getUsername();
            String token = loginRequest.getToken();
            try {
                server.login(username, token, this);
                return new OKResponse();
            } catch (RacesException racesException) {
                return new ErrorResponse(racesException.getMessage());
            }
        }

        if (request instanceof LogoutRequest logoutRequest){
            System.out.println("Logout request");
            User user = logoutRequest.getUser();
            try {
                server.logout(user, this);
                connected=false;
                return new OKResponse();

            } catch (RacesException racesException) {
                return new ErrorResponse(racesException.getMessage());
            }
        }

        return response;
    }
}
