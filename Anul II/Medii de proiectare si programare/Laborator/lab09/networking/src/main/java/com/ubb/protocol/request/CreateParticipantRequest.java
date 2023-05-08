package com.ubb.protocol.request;

import com.ubb.model.Participant;

public class CreateParticipantRequest implements Request {
    private final Participant participant;

    public CreateParticipantRequest(Participant participant) {
        this.participant = participant;
    }

    public Participant getParticipant() {
        return participant;
    }
}
