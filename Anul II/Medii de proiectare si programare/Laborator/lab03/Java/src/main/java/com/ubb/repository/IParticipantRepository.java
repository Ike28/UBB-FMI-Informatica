package com.ubb.repository;

import com.ubb.model.Participant;

import java.util.Collection;

public interface IParticipantRepository extends IRepository<Long, Participant> {
    Collection<Participant> getParticipantsByTeam(final Long teamID);
}
