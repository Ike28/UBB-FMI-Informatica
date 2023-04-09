package com.ubb.protocol.request;

import com.ubb.model.Participant;

public class NewParticipantRequest {
    private final Participant participant;

    public NewParticipantRequest(Participant participant) {
        this.participant = participant;
    }

    public Participant getParticipant() {
        return participant;
    }
}
