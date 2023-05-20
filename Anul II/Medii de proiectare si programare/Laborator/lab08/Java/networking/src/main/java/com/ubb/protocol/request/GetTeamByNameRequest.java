package com.ubb.protocol.request;

public class GetTeamByNameRequest implements Request {
    private final String teamName;

    public GetTeamByNameRequest(String name) {
        this.teamName = name;
    }

    public String getTeamName() {
        return teamName;
    }
}
