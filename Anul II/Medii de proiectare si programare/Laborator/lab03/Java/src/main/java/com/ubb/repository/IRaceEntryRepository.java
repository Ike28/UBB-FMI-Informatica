package com.ubb.repository;

import com.ubb.model.RaceEntry;

import java.util.Collection;

public interface IRaceEntryRepository extends IRepository<Long, RaceEntry> {
    Collection<RaceEntry> getEntriesByRace(Long raceID);
}
