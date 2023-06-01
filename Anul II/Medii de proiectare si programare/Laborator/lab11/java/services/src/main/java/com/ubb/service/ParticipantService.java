package com.ubb.service;

import com.ubb.model.Participant;
import com.ubb.repository.IParticipantRepository;
import com.ubb.validation.IValidator;
import com.ubb.validation.ParticipantValidator;

import java.util.Collection;
import java.util.Optional;

public class ParticipantService implements IParticipantService {
    private final IParticipantRepository participantRepository;
    private final IValidator<Participant> validator;

    public ParticipantService(final IParticipantRepository participantRepository) {
        this.participantRepository = participantRepository;
        validator = new ParticipantValidator();
    }

    @Override
    public Collection<Participant> getParticipantsByTeam(final Long teamID) {
        return participantRepository.getParticipantsByTeam(teamID);
    }

    @Override
    public Optional<Participant> getParticipantByData(Participant participant) {
        return participantRepository.getParticipantByData(participant);
    }

    @Override
    public Optional<Participant> findById(final Long id) {
        return participantRepository.findById(id);
    }

    @Override
    public Collection<Participant> findAll() {
        return participantRepository.findAll();
    }

    @Override
    public void save(final Participant newEntity) {
        validator.validateEntity(newEntity);
        participantRepository.save(newEntity);
    }

    @Override
    public void delete(final Long id) {
        participantRepository.delete(id);
    }

    @Override
    public void update(final Participant updatedEntity) {
        validator.validateEntity(updatedEntity);
        participantRepository.update(updatedEntity);
    }
}
