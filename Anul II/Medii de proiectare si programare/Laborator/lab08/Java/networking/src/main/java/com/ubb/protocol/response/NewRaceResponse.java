package com.ubb.protocol.response;

import com.ubb.dto.RaceDTO;

public class NewRaceResponse implements UpdateResponse {
    private final RaceDTO raceDTO;

    public NewRaceResponse(RaceDTO raceDTO) {
        this.raceDTO = raceDTO;
    }

    public RaceDTO getRaceDTO() {
        return raceDTO;
    }
}
