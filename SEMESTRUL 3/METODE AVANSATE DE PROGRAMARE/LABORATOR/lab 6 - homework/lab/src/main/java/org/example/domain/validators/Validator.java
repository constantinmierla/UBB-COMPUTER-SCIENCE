package org.example.domain.validators;

import java.util.Collection;
public interface Validator<T>{

    void validate(Collection<T> allEntities, T entity) throws ValidationException;
}
