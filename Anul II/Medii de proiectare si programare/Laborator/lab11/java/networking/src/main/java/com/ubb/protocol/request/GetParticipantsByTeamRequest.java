package com.ubb.protocol.request;

public class GetParticipantsByTeamRequest implements Request {
    private final Long teamID;

    public GetParticipantsByTeamRequest(Long teamID) {
        this.teamID = teamID;
    }

    public Long getTeamID() {
        return teamID;
    }
}
