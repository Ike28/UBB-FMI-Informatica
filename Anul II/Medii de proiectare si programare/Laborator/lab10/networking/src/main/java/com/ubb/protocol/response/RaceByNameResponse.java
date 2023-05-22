package com.ubb.protocol.response;

import com.ubb.model.Race;

public class RaceByNameResponse implements Response {
    private final Race race;

    public RaceByNameResponse(Race race) {
        this.race = race;
    }

    public Race getRace() {
        return race;
    }
}
