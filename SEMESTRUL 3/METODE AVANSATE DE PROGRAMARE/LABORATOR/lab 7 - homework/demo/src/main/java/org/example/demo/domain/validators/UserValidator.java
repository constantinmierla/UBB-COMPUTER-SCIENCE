package org.example.demo.domain.validators;

import org.example.demo.domain.User;

import java.util.Collection;
import java.util.Optional;
/**
 * Validates instances of the {@link User} class.
 * Ensures that user attributes meet specified criteria and that users are unique.
 */
public class UserValidator implements Validator<User> {
    /**
     * Validates the specified {@link User} entity against a collection of existing entities.
     *
     * @param allEntities a collection of all existing {@link User} entities
     * @param entity the {@link User} entity to validate
     * @throws ValidationException if the entity's first name or last name is invalid,
     *         or if the user already exists in the collection
     */
    @Override
    public void validate(Collection<User> allEntities, User entity) throws ValidationException {
        Optional.ofNullable(entity.getFirstname())
                .filter(name -> !name.trim().isEmpty())
                .orElseThrow(() -> new ValidationException("invalid user's firstname"));
        Optional.ofNullable(entity.getLastname())
                .filter(name -> !name.trim().isEmpty())
                .orElseThrow(() -> new ValidationException("invalid user's lastname"));
        allEntities.stream()
                .filter(e -> e.getFirstname().equals(entity.getFirstname()) && e.getLastname().equals(entity.getLastname()))
                .findAny()
                .ifPresent(e -> {throw new ValidationException("This user already exists");});
    }
}
