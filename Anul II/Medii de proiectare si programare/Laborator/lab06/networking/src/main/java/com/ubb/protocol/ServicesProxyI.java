package com.ubb.protocol;

import com.ubb.IMainObserver;
import com.ubb.IContestServices;
import com.ubb.exceptions.RacesException;
import com.ubb.model.User;
import com.ubb.protocol.request.LoginRequest;
import com.ubb.protocol.request.LogoutRequest;
import com.ubb.protocol.request.Request;
import com.ubb.protocol.response.ErrorResponse;
import com.ubb.protocol.response.OKResponse;
import com.ubb.protocol.response.Response;
import com.ubb.protocol.response.UpdateResponse;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class ServicesProxyI implements IContestServices {
    private String host;
    private int port;
    private IMainObserver client;

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private Socket connection;

    private BlockingQueue<Response> responseQueue;
    private volatile boolean finished;

    public ServicesProxyI(String host, int port) {
        this.host = host;
        this.port = port;
        responseQueue = new LinkedBlockingQueue<>();
    }

    @Override
    public void login(String username, String password, IMainObserver client) throws RacesException {
        initializeConnection();
        sendRequest(new LoginRequest(username, password));
        Response response = readResponse();
        if (response instanceof OKResponse) {
            this.client = client;
            return;
        }
        if (response instanceof ErrorResponse) {
            closeConnection();
            throw new RacesException(((ErrorResponse) response).getMessage());
        }
    }

    @Override
    public void logout(User user, IMainObserver client) throws RacesException {
        sendRequest(new LogoutRequest(user));
        Response response=readResponse();
        closeConnection();
        if (response instanceof ErrorResponse){
            throw new RacesException(((ErrorResponse) response).getMessage());
        }
    }

    private void initializeConnection() throws RacesException {
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

    private void handleUpdate(UpdateResponse response) {

    }

    private void sendRequest(Request request) throws RacesException {
        try {
            output.writeObject(request);
            output.flush();
        } catch (IOException ioException) {
            throw new RacesException("Error sending object: " + ioException);
        }
    }

    private Response readResponse() throws RacesException {
        Response response = null;
        try {
            response = responseQueue.take();
        } catch (InterruptedException interruptedException) {
            interruptedException.printStackTrace();
        }
        return response;
    }

    private class ReaderThread implements Runnable{
        public void run() {
            while(!finished){
                try {
                    Object response=input.readObject();
                    System.out.println("response received " + response);
                    if (response instanceof UpdateResponse){
                        handleUpdate((UpdateResponse) response);
                    } else {
                        try {
                            responseQueue.put((Response)response);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                } catch (IOException | ClassNotFoundException e) {
                    System.out.println("Reading error "+e);
                }
            }
        }
    }

}
