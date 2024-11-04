package ubb.scs.map.service;

import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Utilizator;
import ubb.scs.map.repository.FriendshipRepository;
import ubb.scs.map.repository.UtilizatorRepository;

import java.util.List;
import java.util.stream.StreamSupport;

/**
 * The UserService class provides services for managing `Utilizator` (User) entities,
 * including ID generation, adding and deleting users.
 */
public class UserService implements Service<Utilizator> {
    private final UtilizatorRepository userRepository;
    private final FriendshipRepository friendshipRepository;

    /**
     * Constructs a UserService with the specified user and friendship repositories.
     *
     * @param userRepo the repository handling user data
     * @param friendRepo the repository handling friendship data
     */
    public UserService(UtilizatorRepository userRepo, FriendshipRepository friendRepo) {
        this.userRepository = userRepo;
        this.friendshipRepository = friendRepo;
    }

    /**
     * Generates a unique ID for a new user by finding the highest existing user ID
     * and returning an incremented value.
     *
     * @return a unique ID of type {@link Long} for the new user
     */
    @Override
    public Long generateID() {
        return StreamSupport.stream(userRepository.findAll().spliterator(), false)
                .mapToLong(Utilizator::getId)
                .max()
                .orElse(0L) + 1;
    }

    /**
     * Retrieves all users from the repository.
     *
     * @return an Iterable collection of all `Utilizator` entities
     */
    public Iterable<Utilizator> getAll(){
        return userRepository.findAll();
    }

    /**
     * Adds a new user to the repository with the specified first and last names.
     * If the user is added successfully, a success message is returned. If the user already exists
     * or an error occurs, the appropriate message is returned.
     *
     * @param firstName the first name of the user
     * @param lastName the last name of the user
     * @return a string message indicating the result of the operation
     */
    public String addUser(String firstName, String lastName) {
        var user = new Utilizator(firstName, lastName);
        user.setId(generateID());

        try {
            var result = this.userRepository.save(user).orElse(null);

            if(result == null)
                return "Utilizator adaugat cu succes!";
            return "Utilizatorul exista deja!";
        }
        catch (Exception e) {
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
        // sterg mai intai prieteniile cu ceilalti useri
        Iterable<Friendship> friendships = friendshipRepository.findAll();
        List<Long> friendshipsToDelete = StreamSupport.stream(friendships.spliterator(), false)
                .filter(friendship -> checkIfUserInFriendship(friendship, id))
                .map(Friendship::getId)
                .toList();

        friendshipsToDelete.forEach(friendshipRepository::delete);

        // sterg utilizatorul
        var result = this.userRepository.delete(id).orElse(null);
        if(result != null)
            return "Utilizator sters cu succes!";
        return "Stergere esuata";
    }
}
