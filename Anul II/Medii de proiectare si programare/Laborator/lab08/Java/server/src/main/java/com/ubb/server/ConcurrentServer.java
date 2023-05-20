package com.ubb.server;

import java.net.Socket;

public abstract class ConcurrentServer extends Server {
    public ConcurrentServer(int port) {
        super(port);
    }

    protected void processRequest(Socket client) {
        Thread worker = createWorker(client);
        worker.start();
    }

    protected abstract Thread createWorker(Socket client);
}
