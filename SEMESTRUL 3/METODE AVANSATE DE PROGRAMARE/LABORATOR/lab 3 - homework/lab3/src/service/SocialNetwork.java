package service;

import domain.*;
import domain.validators.ValidationException;
import repository.InMemoryRepository;
import repository.Repository;

import java.util.*;

/**
 * SocialNetwork class manages users and friendships within a social network.
 * It provides methods to add/remove users, create/remove friendships,
 * and retrieve data about users and their connections.
 */
public class SocialNetwork {

    private final InMemoryRepository<Long, User> repositoryUser;         // Repository for storing users
    private final InMemoryRepository<Long, Friendship> repositoryFriendship;  // Repository for storing friendships

    /**
     * Constructor that initializes the SocialNetwork with user and friendship repositories.
     *
     * @param repositoryUser - repository for managing users
     * @param repositoryFriendship - repository for managing friendships
     */
    public SocialNetwork(InMemoryRepository<Long, User> repositoryUser, InMemoryRepository<Long, Friendship> repositoryFriendship) {
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
        return repositoryUser.findOne(id);
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
            User u = repositoryUser.findOne(id);
            if (u == null) {
                throw new IllegalArgumentException("the user doesn't exist");
            }
            Vector<Long> toDelete = new Vector<>();
            for (Friendship friendship : getFriendships()) {
                if (friendship.getIdUser1().equals(id) || friendship.getIdUser2().equals(id)) {
                    toDelete.add(friendship.getId());
                }
            }
            // Remove all friendships involving this user
            for (Long idToDelete : toDelete) {
                repositoryFriendship.delete(idToDelete);
            }
            User user = repositoryUser.delete(id);
            // Remove this user from all their friends' friend lists
            for (User friend : u.getFriends()) {
                friend.removeFriend(u);
            }
            return user;
        } catch (IllegalArgumentException e) {
            System.out.println("Invalid user");
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
        User user1 = repositoryUser.findOne(friendship.getIdUser1());
        User user2 = repositoryUser.findOne(friendship.getIdUser2());
        if (getFriendships() != null) {
            for (Friendship f : getFriendships()) {
                if (f.getIdUser1().equals(friendship.getIdUser1()) && f.getIdUser2().equals(friendship.getIdUser2())) {
                    throw new ValidationException("The friendship exists");
                }
            }
            if (repositoryUser.findOne(friendship.getIdUser1()) == null || repositoryUser.findOne(friendship.getIdUser2()) == null) {
                throw new ValidationException("The user doesn't exist");
            }
            if (friendship.getIdUser1().equals(friendship.getIdUser2())) {
                throw new ValidationException("IDs can't be the same");
            }
        }

        // Add friendship and update user friend lists
        friendship.setId(getNewFriendshipId());
        repositoryFriendship.save(friendship);

        user1.addFriend(user2);
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
        User user1 = repositoryUser.findOne(id1);
        User user2 = repositoryUser.findOne(id2);

        Long id = 0L;
        for (Friendship f : repositoryFriendship.findAll()) {
            if ((f.getIdUser1().equals(id1) && f.getIdUser2().equals(id2)) || (f.getIdUser1().equals(id2) && f.getIdUser2().equals(id1))) {
                id = f.getId();
            }
        }
        if (id == 0L) {
            throw new IllegalArgumentException("The friendship doesn't exist");
        }
        // Remove friendship from the repository and update user friend lists
        repositoryFriendship.delete(id);

        user1.removeFriend(user2);
        user2.removeFriend(user1);
    }
}
