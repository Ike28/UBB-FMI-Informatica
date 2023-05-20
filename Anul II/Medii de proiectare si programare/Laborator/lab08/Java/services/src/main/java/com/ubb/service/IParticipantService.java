package com.ubb.service;

import com.ubb.model.Participant;

import java.util.Collection;
import java.util.Optional;

public interface IParticipantService extends IService<Long, Participant> {
    Collection<Participant> getParticipantsByTeam(final Long teamID);

    Optional<Participant> getParticipantByData(final Participant participant);
}
