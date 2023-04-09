package com.ubb;

import com.ubb.exceptions.ContestDataException;
import com.ubb.model.*;
import com.ubb.model.data.RaceDTO;

import java.util.Collection;
import java.util.List;
import java.util.Optional;

public interface IContestServices {
    void login(String username, String passwordToken, IMainObserver client) throws ContestDataException;

    void logout(User user, IMainObserver client) throws ContestDataException;

    Collection<Participant> getParticipantsByTeam(final Long teamID) throws ContestDataException;

    Optional<Participant> getParticipantByData(final Participant participant) throws ContestDataException;

    Optional<Race> getRaceByName(String name) throws ContestDataException;

    Collection<RaceEntry> getEntriesByRace(Long raceID) throws ContestDataException;

    Collection<Race> getRacesByEngineCapacity(Integer engineCapacity) throws ContestDataException;

    Collection<RaceDTO> getRacesWithParticipantCount() throws ContestDataException;

    void saveRaceEntries(List<RaceEntry> newEntities) throws ContestDataException;

    Collection<Race> getRacesWhereNotRegisteredAndEngineCapacity(Long participantID, Integer engineCapacity) throws ContestDataException;

    Optional<Team> getTeamByName(String teamName) throws ContestDataException;

    void saveParticipant(final Participant newEntity) throws ContestDataException;

    void saveRace(final Race newEntity) throws ContestDataException;
}
