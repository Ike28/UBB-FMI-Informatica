package com.ubb.protocol.request;

import com.ubb.model.Team;

public class CreateTeamRequest implements Request {
    private final Team team;

    public CreateTeamRequest(Team team) {
        this.team = team;
    }

    public Team getTeam() {
        return team;
    }
}
