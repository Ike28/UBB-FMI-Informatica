package com.ubb.repository;

import com.ubb.model.Participant;

import java.util.Collection;
import java.util.Optional;

public interface IParticipantRepository extends IRepository<Long, Participant> {
    Collection<Participant> getParticipantsByTeam(final Long teamID);

    Optional<Participant> getParticipantByData(final Participant participant);
}
