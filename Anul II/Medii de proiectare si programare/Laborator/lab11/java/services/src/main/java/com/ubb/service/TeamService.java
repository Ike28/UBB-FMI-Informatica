package com.ubb.service;

import com.ubb.model.Team;
import com.ubb.repository.ITeamRepository;
import com.ubb.validation.IValidator;
import com.ubb.validation.TeamValidator;

import java.util.Collection;
import java.util.Optional;

public class TeamService implements ITeamService {
    private final ITeamRepository teamRepository;
    private final IValidator<Team> validator;

    public TeamService(final ITeamRepository teamRepository) {
        this.teamRepository = teamRepository;
        validator = new TeamValidator();
    }

    @Override
    public Optional<Team> findById(Long id) {
        return teamRepository.findById(id);
    }

    @Override
    public Collection<Team> findAll() {
        return teamRepository.findAll();
    }

    @Override
    public void save(Team newEntity) {
        validator.validateEntity(newEntity);
        teamRepository.save(newEntity);
    }

    @Override
    public void delete(Long id) {
        teamRepository.delete(id);
    }

    @Override
    public void update(Team updatedEntity) {
        teamRepository.update(updatedEntity);
    }

    @Override
    public Optional<Team> getTeamByName(String teamName) {
        return teamRepository.getTeamByName(teamName);
    }
}
