package com.ubb.repository;

import com.ubb.model.Identifiable;

import java.util.Collection;

public interface Repository<ID, T extends Identifiable<ID>> {
    T get(ID id);

    Collection<T> read();

    void add(T newEntity);

    void delete(ID id);

    void update(T updatedEntity);
}
