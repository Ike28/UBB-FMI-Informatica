package com.ubb.service;

import com.ubb.model.Race;
import com.ubb.model.RaceEntry;
import com.ubb.model.data.RaceDTO;
import com.ubb.repository.IRaceEntryRepository;
import com.ubb.repository.IRaceRepository;
import com.ubb.validation.IValidator;
import com.ubb.validation.RaceValidator;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Optional;

public class RaceService implements IRaceService {
    private final IRaceRepository raceRepository;
    private final IRaceEntryRepository raceEntryRepository;
    private final IValidator<Race> validator;

    public RaceService(final IRaceRepository raceRepository, final IRaceEntryRepository raceEntryRepository) {
        this.raceEntryRepository = raceEntryRepository;
        this.raceRepository = raceRepository;
        validator = new RaceValidator();
    }

    @Override
    public Collection<RaceDTO> getRacesWithParticipantCount() {
        Collection<RaceDTO> result = new ArrayList<>();
        Collection<Race> races = raceRepository.findAll();
        for (Race race : races) {
            result.add(new RaceDTO(race.getName(), race.getEngineCapacity(),
                    raceEntryRepository.getEntriesByRace(race.getID()).size()));
        }
        return result;
    }

    @Override
    public void saveRaceEntry(RaceEntry newEntity) {
        raceEntryRepository.save(newEntity);
    }

    @Override
    public Collection<Race> getRacesWhereNotRegisteredAndEngineCapacity(Long participantID, Integer engineCapacity) {
        return raceEntryRepository.getRacesWhereNotRegisteredAndEngineCapacity(participantID, engineCapacity);
    }

    @Override
    public Optional<Race> getRaceByName(String name) {
        return raceRepository.getRaceByName(name);
    }

    @Override
    public Collection<RaceEntry> getEntriesByRace(Long raceID) {
        return raceEntryRepository.getEntriesByRace(raceID);
    }

    @Override
    public void deleteByIds(Long participantID, Long raceID) {
        raceEntryRepository.deleteByIds(participantID, raceID);
    }

    @Override
    public Collection<Race> getRacesByEngineCapacity(Integer engineCapacity) {
        return raceRepository.getRacesByEngineCapacity(engineCapacity);
    }

    @Override
    public Optional<Race> findById(Long id) {
        return raceRepository.findById(id);
    }

    @Override
    public Collection<Race> findAll() {
        return raceRepository.findAll();
    }

    @Override
    public void save(Race newEntity) {
        validator.validateEntity(newEntity);
        raceRepository.save(newEntity);
    }

    @Override
    public void delete(Long id) {
        raceRepository.delete(id);
    }

    @Override
    public void update(Race updatedEntity) {
        validator.validateEntity(updatedEntity);
        raceRepository.update(updatedEntity);
    }
}
