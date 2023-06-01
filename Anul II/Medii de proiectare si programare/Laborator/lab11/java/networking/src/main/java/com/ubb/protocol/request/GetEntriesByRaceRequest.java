package com.ubb.protocol.request;

public class GetEntriesByRaceRequest implements Request {
    private final Long raceID;

    public GetEntriesByRaceRequest(Long raceID) {
        this.raceID = raceID;
    }

    public Long getRaceID() {
        return raceID;
    }
}
