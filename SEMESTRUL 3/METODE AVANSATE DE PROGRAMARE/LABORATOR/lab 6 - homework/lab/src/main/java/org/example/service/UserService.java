package org.example.service;

import org.example.domain.Friendship;
import org.example.domain.User;
import org.example.repository.FriendshipDBRepository;
import org.example.repository.UserDBRepository;

import java.util.Collection;
import java.util.List;
import java.util.stream.StreamSupport;

public class UserService {
    private final UserDBRepository userRepository;
    private final FriendshipDBRepository friendshipRepository;

    public UserService(UserDBRepository userRepository, FriendshipDBRepository friendshipRepository) {
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
    }

    public Collection<User> getAll(){
        return userRepository.findAll();
    }

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

        // sterg utilizatorul
        var result = this.userRepository.delete(id);
        if(result.isPresent())
            return "User deleted with success!";
        return "Didn't delete";
    }
}
