package com.ubb.service;

import com.ubb.model.Race;
import com.ubb.model.RaceEntry;
import com.ubb.dto.RaceDTO;

import java.util.Collection;
import java.util.Optional;

public interface IRaceService extends IService<Long, Race> {
    Optional<Race> getRaceByName(String name);

    Collection<RaceEntry> getEntriesByRace(Long raceID);

    void deleteByIds(Long participantID, Long raceID);

    Collection<Race> getRacesByEngineCapacity(Integer engineCapacity);

    Collection<RaceDTO> getRacesWithParticipantCount();

    void saveRaceEntry(RaceEntry newEntity);

    Collection<Race> getRacesWhereNotRegisteredAndEngineCapacity(Long participantID, Integer engineCapacity);
}
