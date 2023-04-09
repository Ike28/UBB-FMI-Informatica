package com.ubb.protocol.response;

import com.ubb.model.data.RaceDTO;

import java.util.List;

public class UpdatedRacesResponse implements UpdateResponse {
    private final List<RaceDTO> races;

    public UpdatedRacesResponse(List<RaceDTO> races) {
        this.races = races;
    }

    public List<RaceDTO> getRaces() {
        return races;
    }
}
