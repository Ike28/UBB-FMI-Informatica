package com.ubb.protocol.response;

import com.ubb.model.Participant;

public class ParticipantResponse implements Response {
    private final Participant participant;

    public ParticipantResponse(Participant participant) {
        this.participant = participant;
    }

    public Participant getParticipant() {
        return participant;
    }
}
