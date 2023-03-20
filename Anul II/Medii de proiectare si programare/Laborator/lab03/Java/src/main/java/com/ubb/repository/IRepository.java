package com.ubb.repository;

import com.ubb.model.Identifiable;

import java.util.Collection;
import java.util.Optional;

public interface IRepository<ID, T extends Identifiable<ID>> {
    Optional<T> get(final ID id);

    Collection<T> read();

    void add(final T newEntity);

    void delete(final ID id);

    void update(final T updatedEntity);
}
