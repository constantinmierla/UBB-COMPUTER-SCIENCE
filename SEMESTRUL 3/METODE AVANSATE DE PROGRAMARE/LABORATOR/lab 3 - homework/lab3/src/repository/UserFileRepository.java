package repository;

import domain.User;
import domain.validators.Validator;

import java.util.*;

/**
 * Repository implementation for managing `User` entities stored in a file.
 * This class extends `AbstractFileRepository` and provides specific implementations
 * for reading and writing `User` entities.
 */
public class UserFileRepository extends AbstractFileRepository<Long, User> {

    /**
     * Constructor that initializes the repository with a filename and a validator.
     * It loads existing users from the file into memory.
     *
     * @param filename  - the name of the file used for storing users
     * @param validator - the validator for validating `User` entities
     */
    public UserFileRepository(String filename, Validator<User> validator) {
        super(filename, validator);
    }

    /**
     * Extracts a `User` entity from a list of attributes (as strings) read from a file.
     * The list of attributes is assumed to contain the ID, first name, and last name of the user.
     *
     * @param attributes - list of attributes extracted from the file
     * @return User - the user entity created from the attributes
     */
    @Override
    public User extractEntity(List<String> attributes) {
        User user = new User(attributes.get(1), attributes.get(2));  // Create user from first and last name
        user.setId(Long.parseLong(attributes.get(0)));  // Set user ID
        return user;
    }

    /**
     * Converts a `User` entity into a string format suitable for writing to a file.
     * The string will contain the user ID, first name, and last name separated by semicolons.
     *
     * @param entity - the `User` entity to be converted to string
     * @return String - the string representation of the `User` entity
     */
    @Override
    protected String createEntityAsString(User entity) {
        return entity.getId() + ";" + entity.getFirstname() + ";" + entity.getLastname();  // Format user attributes as a string
    }
}
