package com.ubb.validation;

import com.ubb.model.Identifiable;

public interface IValidator<T extends Identifiable<?>> {
    void validateEntity(T entity);
}
