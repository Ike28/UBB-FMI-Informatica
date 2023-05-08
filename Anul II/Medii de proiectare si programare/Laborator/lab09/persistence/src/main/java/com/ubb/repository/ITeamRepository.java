package com.ubb.repository;

import com.ubb.model.Team;

import java.util.Optional;

public interface ITeamRepository extends IRepository<Long, Team> {
    Optional<Team> getTeamByName(String teamName);
}
