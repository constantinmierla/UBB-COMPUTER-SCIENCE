package ubb.scs.map.domain.validators;

import ubb.scs.map.domain.Friendship;

import java.util.Collection;

/**
 * Validates instances of the {@link Friendship} class.
 * Ensures that friendships are unique within the collection of existing friendships.
 */
public class FriendshipValidator implements Validator<Friendship> {
    /**
     * Validates the specified {@link Friendship} entity against a collection of existing entities.
     *
     * @param allEntities a collection of all existing {@link Friendship} entities
     * @param friendship the {@link Friendship} entity to validate
     * @throws ValidationException if the friendship already exists in the collection
     */
    @Override
    public void validate(Collection<Friendship> allEntities, Friendship friendship) {
        allEntities.stream()
                .filter(entity -> entity.getFirstUser().equals(friendship.getFirstUser()) &&
                        entity.getSecondUser().equals(friendship.getSecondUser()))
                .findAny()
                .ifPresent(existingFriendship -> { throw new ValidationException("Aceasta prietenie exista deja!"); });
    }
}
