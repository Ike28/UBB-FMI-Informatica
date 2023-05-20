package com.ubb.protocol.request;

public class GetUnregisteredRacesRequest implements Request {
    private final Long participantID;
    private final Integer engineCapacity;

    public GetUnregisteredRacesRequest(Long participantID, Integer engineCapacity) {
        this.participantID = participantID;
        this.engineCapacity = engineCapacity;
    }

    public Long getParticipantID() {
        return participantID;
    }

    public Integer getEngineCapacity() {
        return engineCapacity;
    }
}
