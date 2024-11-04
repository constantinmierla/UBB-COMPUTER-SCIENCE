package repository;

import domain.Friendship;
import domain.validators.Validator;
import domain.Entity;

import java.util.List;

/**
 * Repository implementation for managing `Friendship` entities stored in a file.
 */
public class FriendshipFileRepository extends AbstractFileRepository<Long, Friendship> {

    /**
     * Constructor that initializes the repository with a filename and a validator.
     *
     * @param filename  - the name of the file used for storing friendships
     * @param validator - the validator for validating `Friendship` entities
     */
    public FriendshipFileRepository(String filename, Validator<Friendship> validator) {
        super(filename, validator);
    }

    /**
     * Extracts a `Friendship` entity from a list of attributes.
     *
     * @param attributes - list of attributes extracted from the file
     * @return Friendship - the friendship entity created from the attributes
     */
    @Override
    public Friendship extractEntity(List<String> attributes) {
        Long id1 = Long.parseLong(attributes.get(0));  // Parse first user ID
        Long id2 = Long.parseLong(attributes.get(1));  // Parse second user ID
        return new Friendship(id1, id2);
    }

    /**
     * Converts a `Friendship` entity to a string format for writing to the file.
     *
     * @param entity - the `Friendship` entity
     * @return String - the string representation of the `Friendship` entity
     */
    @Override
    protected String createEntityAsString(Friendship entity) {
        return entity.getIdUser1() + ";" + entity.getIdUser2();  // Format friendship as "ID1;ID2"
    }
}
