package org.example.service;

import org.example.domain.User;
import org.example.domain.Friendship;
import org.example.repository.UserDBRepository;
import org.example.repository.FriendshipDBRepository;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Optional;


public class FriendshipService {
    private final UserDBRepository userDBRepository;
    private final FriendshipDBRepository friendshipDBRepository;

    public FriendshipService(UserDBRepository userDBRepository, FriendshipDBRepository friendshipDBRepository) {
        this.userDBRepository = userDBRepository;
        this.friendshipDBRepository = friendshipDBRepository;
    }

    public Collection<User> getAllFriends(Long id_user) {
        ArrayList<User> friends = new ArrayList<>();
        Iterable<Friendship> friendships = friendshipDBRepository.findAll();

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

    public String addFriendships(Long idFirstUser, Long idSecondUser) {
        var errMsg = "The user with the id was not found: ";
        var user1 = this.userDBRepository.findOne(idFirstUser).orElseThrow(() -> new IllegalArgumentException(errMsg + idFirstUser));
        var user2 = this.userDBRepository.findOne(idSecondUser).orElseThrow(() -> new IllegalArgumentException(errMsg + idSecondUser));
        var friendship = new Friendship(user1, user2);

        try {
            var result = this.friendshipDBRepository.save(friendship);
            if (result.isEmpty()) {
                return "Friendship successfully saved!";
            }
            return "Friendship already exists!";
        }
        catch (Exception e) {
            return e.getMessage();
        }
    }

    private boolean checkIfUsersHaveFriendship(Friendship friendship, Long idFirstUser, Long idSecondUser) {
        if(friendship.getFirstUser().getId().equals(idFirstUser) && friendship.getSecondUser().getId().equals(idSecondUser))
            return true;

        return friendship.getFirstUser().getId().equals(idSecondUser) && friendship.getSecondUser().getId().equals(idFirstUser);
    }

    public String deleteFriendship(Long idFirstUser, Long idSecondUser) {
        Collection<Friendship> friendships = friendshipDBRepository.findAll();

        if(friendships.isEmpty()) {
            return "This user has no friends to be deleted!";
        }

        Optional<Friendship> friendshipToDelete = friendships.stream()
                .filter(friendship -> checkIfUsersHaveFriendship(friendship, idFirstUser, idSecondUser))
                .findFirst();

        if (friendshipToDelete.isPresent()) {
            this.friendshipDBRepository.delete(friendshipToDelete.get().getId());
            return "Friendship successfully deleted!";
        } else {
            return "Friendship not found!";
        }
    }
}
