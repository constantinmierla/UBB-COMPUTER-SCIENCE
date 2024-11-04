package ubb.scs.map.domain.validators;

import java.util.Collection;

/**
 * Represents a validator for entities of type {@code T}.
 *
 * @param <T> the type of the entity to be validated
 */
public interface Validator<T> {
    /**
     * Validates the specified entity against a collection of existing entities.
     *
     * @param allEntities a collection of all existing entities of type {@code T}
     * @param entity the entity to validate
     * @throws ValidationException if the entity is not valid
     */
    void validate(Collection<T> allEntities, T entity) throws ValidationException;
}