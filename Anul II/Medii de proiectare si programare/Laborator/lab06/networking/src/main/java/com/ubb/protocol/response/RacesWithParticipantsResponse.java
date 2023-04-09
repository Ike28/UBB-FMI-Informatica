package com.ubb.protocol.response;

import com.ubb.model.data.RaceDTO;

import java.util.Collection;

public class RacesWithParticipantsResponse implements Response {
    private final Collection<RaceDTO> races;

    public RacesWithParticipantsResponse(Collection<RaceDTO> races) {
        this.races = races;
    }

    public Collection<RaceDTO> getRaces() {
        return races;
    }
}
