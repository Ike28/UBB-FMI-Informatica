package com.ubb.server;

import com.ubb.exceptions.ServerException;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public abstract class Server {
    private final int port;
    private ServerSocket serverSocket = null;

    public Server(int port) {
        this.port = port;
    }

    public void start() throws ServerException {
        try {
            serverSocket = new ServerSocket(port);
            while (true) {
                System.out.println("Waiting for clients...");
                Socket client = serverSocket.accept();
                System.out.println("Client connected.");
                processRequest(client);
            }
        } catch (IOException ioException) {
            throw new ServerException("Server start error:" + ioException.getMessage());
        } finally {
            stop();
        }
    }

    public void stop() throws ServerException {
        try {
            serverSocket.close();
        } catch (IOException ioException) {
            throw new ServerException("Server close error: " + ioException.getMessage());
        }
    }

    protected abstract void processRequest(Socket client);
}
