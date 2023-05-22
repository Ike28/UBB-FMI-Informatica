package com.ubb.protocol.response;

import com.ubb.model.Team;

import java.util.Collection;

public class AllTeamsResponse implements Response {
    private final Collection<Team> teams;

    public AllTeamsResponse(Collection<Team> teams) {
        this.teams = teams;
    }

    public Collection<Team> getTeams() {
        return teams;
    }
}
