package com.ubb.protocol.request;

import com.ubb.model.Race;

public class CreateRaceRequest implements Request {
    private final Race race;

    public CreateRaceRequest(Race race) {
        this.race = race;
    }

    public Race getRace() {
        return race;
    }
}
