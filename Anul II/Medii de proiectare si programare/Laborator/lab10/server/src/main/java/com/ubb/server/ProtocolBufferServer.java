package com.ubb.server;

import com.ubb.IContestServices;
import com.ubb.protocolbuffers.ProtocolBufferWorker;

import java.net.Socket;

public class ProtocolBufferServer extends ConcurrentServer {
    private final IContestServices server;

    public ProtocolBufferServer(int port, IContestServices server) {
        super(port);
        this.server = server;
    }

    @Override
    protected Thread createWorker(Socket client) {
        ProtocolBufferWorker worker = new ProtocolBufferWorker(server, client);
        return new Thread(worker);
    }
}
