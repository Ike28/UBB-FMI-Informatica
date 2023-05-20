package com.ubb.protocol.response;

import com.ubb.dto.RaceDTO;

import java.util.Collection;

public class RacesWithParticipantsResponse implements Response {
    private final Collection<RaceDTO> racesDTO;

    public RacesWithParticipantsResponse(Collection<RaceDTO> racesDTO) {
        this.racesDTO = racesDTO;
    }

    public Collection<RaceDTO> getRacesDTO() {
        return racesDTO;
    }
}
