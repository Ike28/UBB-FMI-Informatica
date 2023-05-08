package com.ubb.repository;

import com.ubb.model.Race;

import java.util.Collection;
import java.util.Optional;

public interface IRaceRepository extends IRepository<Long, Race> {
    Optional<Race> getRaceByName(String name);

    Collection<Race> getRacesByEngineCapacity(Integer engineCapacity);
}
