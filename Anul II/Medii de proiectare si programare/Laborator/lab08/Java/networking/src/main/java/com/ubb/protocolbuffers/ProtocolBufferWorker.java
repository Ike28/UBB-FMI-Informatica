package com.ubb.protocolbuffers;

import com.ubb.IContestServices;
import com.ubb.IMainObserver;
import com.ubb.dto.RaceDTO;
import com.ubb.exceptions.ContestDataException;
import com.ubb.model.Participant;
import com.ubb.model.User;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.List;

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
        // TODO
    }

    @Override
    public void participantAdded(Participant participant) throws ContestDataException {
        // TODO
    }

    @Override
    public void raceEntriesAdded(List<RaceDTO> races) throws ContestDataException {
        // TODO
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
        }

        return null;
    }

    private void sendResponse(BikeContestProtocol.BikeContestResponse response) throws IOException {
        System.out.println("Sending response: " + response);
        response.writeDelimitedTo(outputStream);
        outputStream.flush();
    }
}
