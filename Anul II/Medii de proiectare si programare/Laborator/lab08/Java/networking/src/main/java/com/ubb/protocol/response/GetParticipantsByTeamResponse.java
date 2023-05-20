package com.ubb.protocol.response;

import com.ubb.model.Participant;

import java.util.Collection;

public class GetParticipantsByTeamResponse implements Response {
    private final Collection<Participant> participants;

    public GetParticipantsByTeamResponse(Collection<Participant> participants) {
        this.participants = participants;
    }

    public Collection<Participant> getParticipants() {
        return participants;
    }
}
