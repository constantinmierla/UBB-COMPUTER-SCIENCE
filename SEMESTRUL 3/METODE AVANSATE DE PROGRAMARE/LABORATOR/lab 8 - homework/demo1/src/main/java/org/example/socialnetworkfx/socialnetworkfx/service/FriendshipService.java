package org.example.socialnetworkfx.socialnetworkfx.service;

import org.example.socialnetworkfx.socialnetworkfx.domain.Friendship;
import org.example.socialnetworkfx.socialnetworkfx.domain.User;
import org.example.socialnetworkfx.socialnetworkfx.domain.event.ChangeEventType;
import org.example.socialnetworkfx.socialnetworkfx.domain.event.FriendshipEntityChange;
import org.example.socialnetworkfx.socialnetworkfx.repository.FriendshipDbRepository;
import org.example.socialnetworkfx.socialnetworkfx.repository.UserDbRepository;
import org.example.socialnetworkfx.socialnetworkfx.utils.observer.Observable;
import org.example.socialnetworkfx.socialnetworkfx.utils.observer.Observer;
import org.example.socialnetworkfx.socialnetworkfx.utils.paging.Page;
import org.example.socialnetworkfx.socialnetworkfx.utils.paging.Pageable;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

public class FriendshipService implements Service<Friendship>, Observable<FriendshipEntityChange> {
    FriendshipDbRepository repository;
    UserDbRepository userRepository;
    private List<Observer<FriendshipEntityChange>> observers = new ArrayList<>();

    public FriendshipService(FriendshipDbRepository repository, UserDbRepository userRepository) {
        this.repository = repository;
        this.userRepository = userRepository;
    }

    @Override
    public Friendship delete(Long ID) {
        Friendship a = repository.delete(ID).orElseThrow(() -> new IllegalArgumentException("Service says: invalid ID"));
        FriendshipEntityChange change = new FriendshipEntityChange(ChangeEventType.DELETE, a);
        notifyObservers(change);
        return a;
    }

    public Friendship save(Long ID1, Long ID2) {
        Friendship friendship = new Friendship(ID1, ID2);
        Friendship a = repository.save(friendship).orElse(null);
        FriendshipEntityChange event = new FriendshipEntityChange(ChangeEventType.ADD, friendship);
        notifyObservers(event);
        return a;
    }



    @Override
    public Iterable<Friendship> findAll() {
        return repository.findAll();
    }

    public ArrayList<User> getFriends(Long ID,Iterable<Friendship> friendships) {
        ArrayList<User> friends = new ArrayList<>();
        friendships.forEach(friendship -> {
            if (friendship.getFirstFriend().equals(ID)) {
                User friend = userRepository.findOne(friendship.getSecondFriend()).orElseThrow(() -> new IllegalArgumentException("User not found"));
                friends.add(friend);
            } else if (friendship.getSecondFriend().equals(ID)) {
                User friend = userRepository.findOne(friendship.getFirstFriend()).orElseThrow(() -> new IllegalArgumentException("User not found"));
                friends.add(friend);
            }
        });
        return friends.stream().sorted(Comparator.comparing(User::getID)).collect(Collectors.toCollection(ArrayList::new));
    }

    public Page<Friendship> findAllOnPage(Pageable page,Long ID) {
            return repository.findAllOnPage(page,ID);
    }


    public Friendship findOne(Long ID1, Long ID2) {
        Iterable<Friendship> friendships = repository.findAll();
        for (Friendship friendship : friendships) {
            if (friendship.getFirstFriend().equals(ID1) && friendship.getSecondFriend().equals(ID2)) {
                return friendship;
            }
            if (friendship.getSecondFriend().equals(ID1) && friendship.getFirstFriend().equals(ID2)) {
                return friendship;
            }
        }
        return null;
    }

    @Override
    public void addObserver(Observer<FriendshipEntityChange> e) {
        observers.add(e);

    }

    @Override
    public void removeObserver(Observer<FriendshipEntityChange> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(FriendshipEntityChange t) {

        observers.stream().forEach(x -> x.update(t));
    }

    public void removeAllByID(Long ID) {
        Iterable<Friendship> friendships = repository.findAll();
        for (Friendship friend : friendships) {
            if (friend.getFirstFriend().equals(ID) || friend.getSecondFriend().equals(ID)) {
                repository.delete(friend.getID());
            }
        }
    }
    public ArrayList<User> showNonFriends(Long ID){
        ArrayList<User> friends = getFriends(ID,repository.findAll());
        ArrayList<User> usersList = new ArrayList<>();
        Iterable<User> users = userRepository.findAll();
        for(User user : users){
            if(!friends.contains(user)){
                if(!user.getID().equals(ID)) {
                    usersList.add(user);
                }
            }
        }
        return usersList;
    }
}
