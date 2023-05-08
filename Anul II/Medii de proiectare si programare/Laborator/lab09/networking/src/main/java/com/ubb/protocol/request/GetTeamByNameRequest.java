package com.ubb.protocol.request;

public class GetTeamByNameRequest implements Request {
    private final String name;

    public GetTeamByNameRequest(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}
