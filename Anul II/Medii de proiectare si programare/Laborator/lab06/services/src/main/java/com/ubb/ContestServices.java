package com.ubb;

import com.ubb.exceptions.ContestDataException;
import com.ubb.model.*;
import com.ubb.dto.RaceDTO;
import com.ubb.service.IParticipantService;
import com.ubb.service.IRaceService;
import com.ubb.service.ITeamService;
import com.ubb.service.IUserService;

import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ContestServices implements IContestServices {
    private final IUserService userService;
    private final IParticipantService participantService;
    private final IRaceService raceService;
    private final ITeamService teamService;

    private final Map<String, IMainObserver> loggedClients;
    private static final int DEFAULT_THREADS = 8;

    public ContestServices(IUserService userService, IParticipantService participantService, IRaceService raceService,
                           ITeamService teamService) {
        this.userService = userService;
        this.participantService = participantService;
        this.raceService = raceService;
        this.teamService = teamService;
        loggedClients = new ConcurrentHashMap<>();
    }

    @Override
    public synchronized User login(String username, String passwordToken, IMainObserver client) throws ContestDataException {
        Optional<User> foundUser = userService.getLogin(username, passwordToken);
        if (foundUser.isPresent()) {
            if (loggedClients.get(username) != null) {
                throw new ContestDataException("User already logged in.");
            }
            loggedClients.put(username, client);
        } else {
            throw new ContestDataException("Authentication failed.");
        }
        return foundUser.get();
    }

    @Override
    public synchronized void logout(User user, IMainObserver client) throws ContestDataException {
        IMainObserver localClient = loggedClients.remove(user.getUsername());
        if (localClient == null) {
            throw new ContestDataException("User " + user.getUsername() + " is not logged in.");
        }
    }

    @Override
    public synchronized Collection<Participant> getParticipantsByTeam(Long teamID) {
        return participantService.getParticipantsByTeam(teamID);
    }

    @Override
    public synchronized Optional<Participant> getParticipantByData(Participant participant) {
        return participantService.getParticipantByData(participant);
    }

    @Override
    public synchronized Optional<Race> getRaceByName(String name) {
        return raceService.getRaceByName(name);
    }

    @Override
    public synchronized Collection<RaceEntry> getEntriesByRace(Long raceID) {
        return raceService.getEntriesByRace(raceID);
    }

    @Override
    public synchronized Collection<Race> getRacesByEngineCapacity(Integer engineCapacity) {
        return raceService.getRacesByEngineCapacity(engineCapacity);
    }

    @Override
    public synchronized Collection<RaceDTO> getRacesWithParticipantCount() {
        return raceService.getRacesWithParticipantCount();
    }

    @Override
    public void saveRaceEntries(List<RaceEntry> newEntities) {
        newEntities.forEach(raceService::saveRaceEntry);

        ExecutorService executor = Executors.newFixedThreadPool(DEFAULT_THREADS);
        for (IMainObserver client : loggedClients.values()) {
            executor.execute(() -> {
                try {
                    client.raceEntriesAdded(raceService.getRacesWithParticipantCount().stream().toList());
                } catch (ContestDataException e) {
                    e.printStackTrace();
                }
            });
        }
        executor.shutdown();
    }

    @Override
    public synchronized Collection<Race> getRacesWhereNotRegisteredAndEngineCapacity(Long participantID, Integer engineCapacity) {
        return raceService.getRacesWhereNotRegisteredAndEngineCapacity(participantID, engineCapacity);
    }

    @Override
    public synchronized Optional<Team> getTeamByName(String teamName) {
        return teamService.getTeamByName(teamName);
    }

    @Override
    public void saveParticipant(Participant newEntity) throws ContestDataException {
        participantService.save(newEntity);
        ExecutorService executor = Executors.newFixedThreadPool(DEFAULT_THREADS);
        for (IMainObserver client : loggedClients.values()) {
            executor.execute(() -> {
                try {
                    client.participantAdded(newEntity);
                } catch (ContestDataException e) {
                    e.printStackTrace();
                }
            });
        }
        executor.shutdown();
    }

    @Override
    public void saveRace(Race newEntity) throws ContestDataException {
        raceService.save(newEntity);
        Optional<Race> result = raceService.getRaceByName(newEntity.getName());
        if (result.isPresent()) {
            for (IMainObserver client : loggedClients.values()) {
                client.raceAdded(new RaceDTO(result.get().getName(), result.get().getEngineCapacity(),
                        raceService.getEntriesByRace(result.get().getID()).size()));
            }
            ExecutorService executor = Executors.newFixedThreadPool(DEFAULT_THREADS);
            for (IMainObserver client : loggedClients.values()) {
                executor.execute(() -> {
                    try {
                        client.raceAdded(new RaceDTO(result.get().getName(), result.get().getEngineCapacity(),
                                raceService.getEntriesByRace(result.get().getID()).size()));
                    } catch (ContestDataException e) {
                        e.printStackTrace();
                    }
                });
            }
            executor.shutdown();
        }
    }

    @Override
    public synchronized Collection<Team> findAllTeams() throws ContestDataException {
        return teamService.findAll();
    }

    @Override
    public synchronized Collection<Participant> findAllParticipants() {
        return participantService.findAll();
    }
}
