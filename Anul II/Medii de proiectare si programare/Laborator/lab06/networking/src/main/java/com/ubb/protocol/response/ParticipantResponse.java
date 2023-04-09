package com.ubb.protocol.response;

import com.ubb.model.Participant;

import java.util.Optional;

public class ParticipantResponse implements Response {
    private final Optional<Participant> participant;

    public ParticipantResponse(Optional<Participant> participant) {
        this.participant = participant;
    }

    public Optional<Participant> getParticipant() {
        return participant;
    }
}
