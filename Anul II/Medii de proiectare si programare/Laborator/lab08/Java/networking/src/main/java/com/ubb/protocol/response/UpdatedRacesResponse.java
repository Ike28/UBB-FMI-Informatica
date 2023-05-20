package com.ubb.protocol.response;

import com.ubb.dto.RaceDTO;

import java.util.List;

public class UpdatedRacesResponse implements UpdateResponse {
    private final List<RaceDTO> racesDTO;

    public UpdatedRacesResponse(List<RaceDTO> racesDTO) {
        this.racesDTO = racesDTO;
    }

    public List<RaceDTO> getRacesDTO() {
        return racesDTO;
    }
}
