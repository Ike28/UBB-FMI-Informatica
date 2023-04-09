package com.ubb.protocol.response;

import com.ubb.model.Team;

import java.util.Optional;

public class TeamResponse implements Response {
    private final Optional<Team> team;

    public TeamResponse(Optional<Team> team) {
        this.team = team;
    }

    public Optional<Team> getTeam() {
        return team;
    }
}
