package org.example.socialnetworkfx.socialnetworkfx.service;

import org.controlsfx.control.tableview2.filter.filtereditor.SouthFilter;
import org.example.socialnetworkfx.socialnetworkfx.domain.Friendship;
import org.example.socialnetworkfx.socialnetworkfx.domain.User;
import org.example.socialnetworkfx.socialnetworkfx.domain.event.ChangeEventType;
import org.example.socialnetworkfx.socialnetworkfx.domain.event.FriendshipEntityChange;
import org.example.socialnetworkfx.socialnetworkfx.domain.event.UserEntityChange;
import org.example.socialnetworkfx.socialnetworkfx.repository.FriendshipDbRepository;
import org.example.socialnetworkfx.socialnetworkfx.repository.UserDbRepository;
import org.example.socialnetworkfx.socialnetworkfx.utils.Observable;
import org.example.socialnetworkfx.socialnetworkfx.utils.Observer;

import java.util.ArrayList;
import java.util.List;

public class FriendshipService implements Service<Friendship>, Observable<FriendshipEntityChange> {
    FriendshipDbRepository repository;
    UserDbRepository userRepository;
    private List<Observer<FriendshipEntityChange>> observers=new ArrayList<>();

    public FriendshipService(FriendshipDbRepository repository, UserDbRepository userRepository) {
        this.repository = repository;
        this.userRepository = userRepository;
    }

    @Override
    public Friendship delete(Long ID) {
        Friendship a=repository.delete(ID).orElseThrow(() -> new IllegalArgumentException("Service says: invalid ID"));
        FriendshipEntityChange change=new FriendshipEntityChange(ChangeEventType.DELETE,a);
        notifyObservers(change);
        return a;
    }

    public Friendship save(Long ID1, Long ID2) {
        Friendship friendship = new Friendship(ID1, ID2);
        Friendship a=repository.save(friendship).orElse(null);
        FriendshipEntityChange event=new FriendshipEntityChange(ChangeEventType.ADD, friendship);
        notifyObservers(event);
        return a;
    }

    @Override
    public Iterable<Friendship> findAll() {
        return repository.findAll();
    }
    public ArrayList<User> getFriends(Long ID){
        ArrayList<User> friends = new ArrayList<>();
        Iterable<Friendship> friendships = repository.findAll();
        friendships.forEach(friendship->{
            if(friendship.getFirstFriend().equals(ID)) {
                User friend=userRepository.findOne(friendship.getSecondFriend()).orElseThrow(() -> new IllegalArgumentException("User not found"));
                friends.add(friend);
            }
            else if(friendship.getSecondFriend().equals(ID)) {
                User friend=userRepository.findOne(friendship.getFirstFriend()).orElseThrow(() -> new IllegalArgumentException("User not found"));
                friends.add(friend);
            }
        });
        return friends;
    }
    public Friendship findOne(Long ID1,Long ID2){
        Iterable<Friendship> friendships = repository.findAll();
        for(Friendship friendship:friendships){
            if(friendship.getFirstFriend().equals(ID1) && friendship.getSecondFriend().equals(ID2)) {
                return friendship;
            }
            if(friendship.getSecondFriend().equals(ID1) && friendship.getFirstFriend().equals(ID2)) {
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
        //observers.remove(e);
    }

    @Override
    public void notifyObservers(FriendshipEntityChange t) {

        observers.stream().forEach(x->x.update(t));
    }
}
