package com.ubb.repository;

import com.ubb.model.Identifiable;

import java.util.Collection;
import java.util.Optional;

public interface IRepository<ID, T extends Identifiable<ID>> {
    Optional<T> findById(final ID id);

    Collection<T> findAll();

    void save(final T newEntity);

    void delete(final ID id);

    void update(final T updatedEntity);
}
