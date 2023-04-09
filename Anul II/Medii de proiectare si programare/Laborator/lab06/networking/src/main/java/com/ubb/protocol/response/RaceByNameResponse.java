package com.ubb.protocol.response;

import com.ubb.model.Race;

import java.util.Optional;

public class RaceByNameResponse implements Response {
    private final Optional<Race> race;

    public RaceByNameResponse(Optional<Race> race) {
        this.race = race;
    }

    public Optional<Race> getRace() {
        return race;
    }
}
