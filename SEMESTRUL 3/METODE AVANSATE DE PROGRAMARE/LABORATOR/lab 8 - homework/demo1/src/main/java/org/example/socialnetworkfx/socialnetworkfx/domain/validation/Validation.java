package org.example.socialnetworkfx.socialnetworkfx.domain.validation;

public interface Validation<T>{
    void validate(T entity) throws ValidationException;
    }

