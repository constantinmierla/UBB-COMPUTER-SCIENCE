package ubb.scs.map.domain.validators;


import ubb.scs.map.domain.Utilizator;

import java.util.Collection;
import java.util.Optional;

/**
 * Validates instances of the {@link Utilizator} class.
 * Ensures that user attributes meet specified criteria and that users are unique.
 */
public class UtilizatorValidator implements Validator<Utilizator> {
    /**
     * Validates the specified {@link Utilizator} entity against a collection of existing entities.
     *
     * @param allEntities a collection of all existing {@link Utilizator} entities
     * @param entity the {@link Utilizator} entity to validate
     * @throws ValidationException if the entity's first name or last name is invalid,
     *         or if the user already exists in the collection
     */
    @Override
    public void validate(Collection<Utilizator> allEntities, Utilizator entity) throws ValidationException {
        Optional.ofNullable(entity.getFirstName())
                .filter(name -> !name.trim().isEmpty())
                .orElseThrow(() -> new ValidationException("Prenumele utilizatorului nu este valid"));

        Optional.ofNullable(entity.getLastName())
                .filter(name -> !name.trim().isEmpty())
                .orElseThrow(() -> new ValidationException("Numele de familie al utilizatorului nu este valid"));

        allEntities.stream()
                .filter(e -> e.getFirstName().equals(entity.getFirstName()) && e.getLastName().equals(entity.getLastName()))
                .findAny()
                .ifPresent(existingUser -> { throw new ValidationException("Acest utilizator exista deja!"); });
    }
}
