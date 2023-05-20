package com.ubb.service;

import com.ubb.model.Team;

import java.util.Optional;

public interface ITeamService extends IService<Long, Team> {
    Optional<Team> getTeamByName(String teamName);
}
