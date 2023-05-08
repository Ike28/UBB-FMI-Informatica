package com.ubb.repository;

import com.ubb.model.Race;
import com.ubb.model.RaceEntry;

import java.util.Collection;

public interface IRaceEntryRepository extends IRepository<Long, RaceEntry> {
    Collection<RaceEntry> getEntriesByRace(Long raceID);

    void deleteByIds(Long participantID, Long raceID);

    Collection<Race> getRacesWhereNotRegisteredAndEngineCapacity(Long participantID, Integer engineCc);
}
