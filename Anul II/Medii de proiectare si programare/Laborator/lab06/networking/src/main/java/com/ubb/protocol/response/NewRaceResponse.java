package com.ubb.protocol.response;

import com.ubb.model.data.RaceDTO;

public class NewRaceResponse implements UpdateResponse {
    private final RaceDTO race;

    public NewRaceResponse(RaceDTO race) {
        this.race = race;
    }

    public RaceDTO getRace() {
        return race;
    }
}
