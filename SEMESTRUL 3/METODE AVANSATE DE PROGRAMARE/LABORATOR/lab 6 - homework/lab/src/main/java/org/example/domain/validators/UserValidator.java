package org.example.domain.validators;

import org.example.domain.User;
import java.util.Collection;
import java.util.Optional;
/**
 * Validates instances of the {@link User} class.
 * Ensures that user attributes meet specified criteria and that users are unique.
 */
public class UserValidator implements Validator<User> {

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
