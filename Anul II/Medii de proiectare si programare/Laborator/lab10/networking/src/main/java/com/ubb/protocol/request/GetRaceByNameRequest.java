package com.ubb.protocol.request;

public class GetRaceByNameRequest implements Request {
    private final String raceName;

    public GetRaceByNameRequest(String raceName) {
        this.raceName = raceName;
    }

    public String getRaceName() {
        return raceName;
    }
}
