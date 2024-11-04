package service;

import domain.*;
import domain.validators.ValidationException;
import repository.FriendshipFileRepository;
import repository.InMemoryRepository;
import repository.Repository;
import repository.UserFileRepository;

import java.util.*;

/**
 * SocialNetwork class manages users and friendships within a social network.
 * It provides methods to add/remove users, create/remove friendships,
 * and retrieve data about users and their connections.
 */
public class SocialNetwork {

    private final UserFileRepository repositoryUser;         // Repository for storing users
    private final FriendshipFileRepository repositoryFriendship;  // Repository for storing friendships

    /**
     * Constructor that initializes the SocialNetwork with user and friendship repositories.
     *
     * @param repositoryUser - repository for managing users
     * @param repositoryFriendship - repository for managing friendships
     */
    public SocialNetwork(UserFileRepository repositoryUser, FriendshipFileRepository repositoryFriendship) {
        this.repositoryUser = repositoryUser;
        this.repositoryFriendship = repositoryFriendship;
    }

    /**
     * Returns an iterable collection of all users in the network.
     *
     * @return Iterable<User> - all users
     */
    public Iterable<User> getUsers() {
        return repositoryUser.findAll();
    }

    /**
     * Finds and returns a user by their ID.
     *
     * @param id - the ID of the user to be found
     * @return User - the user with the given ID or null if not found
     */
    public User findUser(Long id) {
        return repositoryUser.findOne(id).orElseThrow(() -> new ValidationException("No user"));
    }

    /**
     * Generates a new unique ID for users by incrementing the highest existing user ID.
     *
     * @return Long - the new unique user ID
     */
    public Long getNewUserId() {
        Long id = 0L;
        for (User u : repositoryUser.findAll()) {
            id = u.getId();
        }
        id++;
        return id;
    }

    /**
     * Adds a new user to the network. The user receives a unique ID.
     *
     * @param user - the User object to be added
     */
    public void addUser(User user) {
        user.setId(getNewUserId());
        repositoryUser.save(user);
    }

    /**
     * Returns an iterable collection of all friendships in the network.
     *
     * @return Iterable<Friendship> - all friendships
     */
    public Iterable<Friendship> getFriendships() {
        return repositoryFriendship.findAll();
    }

    /**
     * Removes a user and all their associated friendships from the network.
     * It ensures that all friendships involving this user are removed as well.
     *
     * @param id - the ID of the user to be removed
     * @return User - the removed user or null if the user doesn't exist
     */
    public User removeUser(Long id) {
        try {
            User u = repositoryUser.findOne(id).orElseThrow(() -> new ValidationException("User doesn't exist!"));
            Vector<Long> toDelete = new Vector<>();
            getFriendships().forEach(friendship -> {
                if (friendship.getIdUser2().equals(id) || friendship.getIdUser1().equals(id)) {
                    toDelete.add(friendship.getId());
                }
            });
            toDelete.forEach(repositoryFriendship::delete);
            User user = repositoryUser.delete(id).orElseThrow(() -> new ValidationException("User doesn't exist!"));
            u.getFriends().forEach(friend -> friend.removeFriend(u));
            return user;
        } catch (IllegalArgumentException e) {
            System.out.println("Invalid user! ");
        } catch (ValidationException v) {
            System.out.println();
        }
        return null;
    }

    /**
     * Generates a new unique ID for friendships by incrementing the highest existing friendship ID.
     *
     * @return Long - the new unique friendship ID
     */
    public Long getNewFriendshipId() {
        Long id = 0L;
        for (Friendship f : repositoryFriendship.findAll()) {
            id = f.getId();
        }
        id++;
        return id;
    }

    /**
     * Adds a new friendship between two users. It verifies that the friendship does not already exist,
     * and that both users exist in the network.
     *
     * @param friendship - the Friendship object representing the new friendship
     * @throws ValidationException - if the friendship already exists, if the users don't exist, or if IDs are the same
     */
    public void addFriendship(Friendship friendship) {
        User user1 = null;
        User user2 = null;
        try {
            user1 = repositoryUser.findOne(friendship.getIdUser1()).orElseThrow(ValidationException::new);
            user2 = repositoryUser.findOne(friendship.getIdUser2()).orElseThrow(ValidationException::new);
        } catch (ValidationException v) {
            System.out.println();
        }
        if (getFriendships() != null) {
            getFriendships().forEach(f -> {
                if (f.getIdUser1().equals(friendship.getIdUser1()) && f.getIdUser2().equals(friendship.getIdUser2())) {
                    throw new ValidationException("The friendship already exist! ");
                }
            });
            if (repositoryUser.findOne(friendship.getIdUser1()).isEmpty() || repositoryUser.findOne(friendship.getIdUser2()).isEmpty()) {
                throw new ValidationException("User doesn't exist! ");
            }
            if (friendship.getIdUser1().equals(friendship.getIdUser2()))
                throw new ValidationException("IDs can't be the same!!! ");
        }
        friendship.setId(getNewFriendshipId());
        repositoryFriendship.save(friendship);

        assert user1 != null;
        user1.addFriend(user2);
        assert user2 != null;
        user2.addFriend(user1);
    }

    /**
     * Removes a friendship between two users. If the friendship exists, it deletes it from both
     * the repository and each user's list of friends.
     *
     * @param id1 - the ID of the first user
     * @param id2 - the ID of the second user
     * @throws IllegalArgumentException - if the friendship doesn't exist
     */
    public void removeFriendship(Long id1, Long id2) {
        User user1 = null;
        User user2 = null;
        try {
            user1 = repositoryUser.findOne(id1).orElseThrow(() -> new ValidationException("User with id " + id1 + " doesn't exist!"));
            user2 = repositoryUser.findOne(id2).orElseThrow(() -> new ValidationException("User with id " + id2 + " doesn't exist!"));
        } catch (ValidationException v) {
            System.out.println();
        }
        Long id = 0L;
        for (Friendship f : repositoryFriendship.findAll()) {
            if ((f.getIdUser1().equals(id1) && f.getIdUser2().equals(id2)) || (f.getIdUser1().equals(id2) && f.getIdUser2().equals(id1)))
                id = f.getId();
        }
        if (id == 0L)
            throw new IllegalArgumentException("The friendship doesn't exist!");
        repositoryFriendship.delete(id);

        assert user1 != null;
        user1.removeFriend(user2);
        assert user2 != null;
        user2.removeFriend(user1);
    }
}
