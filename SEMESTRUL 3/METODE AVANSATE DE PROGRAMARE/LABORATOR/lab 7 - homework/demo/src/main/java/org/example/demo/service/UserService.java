package org.example.service;

import org.example.domain.Friendship;
import org.example.domain.User;
import org.example.repository.FriendshipDBRepository;
import org.example.repository.UserDBRepository;

import java.util.Collection;
import java.util.List;
import java.util.stream.StreamSupport;

/**
 * The UserService class provides services for managing `User` (User) entities,
 * including ID generation, adding and deleting users.
 */
public class UserService {
    private final UserDBRepository userRepository;
    private final FriendshipDBRepository friendshipRepository;

    /**
     * Constructs a UserService with the specified user and friendship repositories.
     *
     * @param userRepository the repository handling user data
     * @param friendshipRepository the repository handling friendship data
     */
    public UserService(UserDBRepository userRepository, FriendshipDBRepository friendshipRepository) {
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
    }

    /**
     * Retrieves all users from the repository.
     *
     * @return an Iterable collection of all `User` entities
     */
    public Collection<User> getAll(){
        return userRepository.findAll();
    }

    /**
     * Adds a new user to the repository with the specified first and last names.
     * If the user is added successfully, a success message is returned. If the user already exists
     * or an error occurs, the appropriate message is returned.
     *
     * @param firstname the first name of the user
     * @param lastname the last name of the user
     * @return a string message indicating the result of the operation
     */
    public String addUser(String firstname, String lastname){
        try{
            var result = this.userRepository.save(new User(firstname, lastname));

            if(result.isEmpty()){
                return "Success - User added";
            }
            return "User already added";
        }catch (Exception e){
            return e.getMessage();
        }
    }
    /**
     * Checks if a specified user, identified by their ID, is part of a given friendship.
     *
     * @param friendship the {@link Friendship} instance to check
     * @param idUser the ID of the user to verify as part of the friendship
     * @return {@code true} if the user with the specified ID is either the first or second user
     *         in the friendship; {@code false} otherwise
     */
    private boolean checkIfUserInFriendship(Friendship friendship, Long idUser) {
        return friendship.getFirstUser().getId().equals(idUser) || friendship.getSecondUser().getId().equals(idUser);
    }

    /**
     * Deletes a user with the specified ID, along with their friendships.
     * A success or failure message is returned based on the operation's outcome.
     *
     * @param id the ID of the user to delete
     * @return a string message indicating whether the user was successfully deleted
     */
    public String deleteUser(Long id) {
        Iterable<Friendship> friendships = friendshipRepository.findAll();
        List<Long> friendshipsToDelete = StreamSupport.stream(friendships.spliterator(), false)
                .filter(friendship -> checkIfUserInFriendship(friendship, id))
                .map(Friendship::getId)
                .toList();

        friendshipsToDelete.forEach(friendshipRepository::delete);

        var result = this.userRepository.delete(id);
        if(result.isPresent())
            return "User deleted with success!";
        return "Didn't delete";
    }
}
