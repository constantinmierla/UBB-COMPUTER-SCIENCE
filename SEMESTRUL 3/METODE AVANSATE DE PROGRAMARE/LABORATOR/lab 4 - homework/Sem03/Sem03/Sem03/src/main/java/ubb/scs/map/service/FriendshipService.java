package ubb.scs.map.service;

import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Utilizator;
import ubb.scs.map.repository.FriendshipRepository;
import ubb.scs.map.repository.UtilizatorRepository;

import java.util.ArrayList;
import java.util.Optional;
import java.util.stream.StreamSupport;

/**
 * The FriendshipService class provides services for managing `Friendship` entities,
 * including ID generation, adding and deleting friendships, and retrieving a user's friends.
 */
public class FriendshipService implements Service<Friendship>{
    private final UtilizatorRepository utilizatorRepository;
    private final FriendshipRepository friendshipRepository;

    /**
     * Constructs a FriendshipService with the specified user and friendship repositories.
     *
     * @param utilizatorRepository the repository handling user data
     * @param friendshipRepository the repository handling friendship data
     */
    public FriendshipService(UtilizatorRepository utilizatorRepository, FriendshipRepository friendshipRepository) {
        this.utilizatorRepository = utilizatorRepository;
        this.friendshipRepository = friendshipRepository;
    }


    /**
     * Generates a unique ID for a new friendship.
     *
     * @return a unique ID of type {@link Long} for the new friendship
     */
    @Override
    public Long generateID(){
        return StreamSupport.stream(friendshipRepository.findAll().spliterator(), false)
                .mapToLong(Friendship::getId)
                .max()
                .orElse(0L) + 1;
    }

    /**
     * Retrieves all friends of a specified user.
     *
     * @param id_user the ID of the user whose friends are to be retrieved
     * @return an Iterable collection of `Utilizator` entities representing the user's friends
     */
    public Iterable<Utilizator> getAllFriends(Long id_user) {
        ArrayList<Utilizator> friends = new ArrayList<>();
        Iterable<Friendship> friendships = friendshipRepository.findAll();

        friendships.forEach(friendship -> {
            if(friendship.getFirstUser().getId().equals(id_user)) {
                friends.add(friendship.getSecondUser());
            }
            else if(friendship.getSecondUser().getId().equals(id_user)) {
                friends.add(friendship.getFirstUser());
            }
        });

        return friends;
    }

    /**
     * Adds a new friendship between two users identified by their IDs.
     *
     * @param idFirstUser the ID of the first user
     * @param idSecondUser the ID of the second user
     * @return a string message indicating the result of the operation
     */
    public String addFriendships(Long idFirstUser, Long idSecondUser) {
        var errMsg = "Nu a fost gasit utilizatorul cu id-ul: ";
        var user1 = this.utilizatorRepository.findOne(idFirstUser).orElseThrow(() -> new IllegalArgumentException(errMsg + idFirstUser));
        var user2 = this.utilizatorRepository.findOne(idSecondUser).orElseThrow(() -> new IllegalArgumentException(errMsg + idSecondUser));
        var friendship = new Friendship(user1, user2);
        friendship.setId(this.generateID());

        try {
            var result = this.friendshipRepository.save(friendship).orElse(null);
            if (result == null) {
                return "Prietenie salvata cu succes!";
            }
            return "Prietenia exista deja!";
        }
        catch (Exception e) {
            return e.getMessage();
        }
    }

    /**
     * Checks if a given friendship exists between two specified users.
     *
     * @param friendship the {@link Friendship} object representing the friendship to check
     * @param idFirstUser the ID of the first user in the potential friendship
     * @param idSecondUser the ID of the second user in the potential friendship
     * @return {@code true} if the friendship exists between the specified users, {@code false} otherwise
     */
    private boolean checkIfUsersHaveFriendship(Friendship friendship, Long idFirstUser, Long idSecondUser) {
        if(friendship.getFirstUser().getId().equals(idFirstUser) && friendship.getSecondUser().getId().equals(idSecondUser))
            return true;

        return friendship.getFirstUser().getId().equals(idSecondUser) && friendship.getSecondUser().getId().equals(idFirstUser);
    }

    /**
     * Deletes a friendship between two users identified by their IDs.
     *
     * @param idFirstUser the ID of the first user
     * @param idSecondUser the ID of the second user
     * @return a string message indicating whether the friendship was successfully deleted
     */
    public String deleteFriendship(Long idFirstUser, Long idSecondUser) {
        Iterable<Friendship> friendships = friendshipRepository.findAll();

        Optional<Friendship> friendshipToDelete = StreamSupport.stream(friendships.spliterator(), false)
                .filter(friendship -> checkIfUsersHaveFriendship(friendship, idFirstUser, idSecondUser))
                .findFirst();

        if (friendshipToDelete.isPresent()) {
            this.friendshipRepository.delete(friendshipToDelete.get().getId());
            return "Prietenie stearsa cu succes!";
        } else {
            return "Prietenia nu a fost gasita!";
        }
    }
}
