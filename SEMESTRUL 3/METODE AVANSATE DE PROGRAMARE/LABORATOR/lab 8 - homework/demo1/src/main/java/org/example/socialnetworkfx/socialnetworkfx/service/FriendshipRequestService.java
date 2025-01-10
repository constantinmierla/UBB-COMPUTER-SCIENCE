package org.example.socialnetworkfx.socialnetworkfx.service;

import org.example.socialnetworkfx.socialnetworkfx.domain.FriendshipRequest;
import org.example.socialnetworkfx.socialnetworkfx.domain.event.ChangeEventType;
import org.example.socialnetworkfx.socialnetworkfx.domain.event.RequestEntityChange;
import org.example.socialnetworkfx.socialnetworkfx.repository.FriendshipRequestDbRepository;
import org.example.socialnetworkfx.socialnetworkfx.utils.observer.Observable;
import org.example.socialnetworkfx.socialnetworkfx.utils.observer.Observer;

import java.util.ArrayList;
import java.util.List;

public class FriendshipRequestService implements Service<FriendshipRequest>, Observable<RequestEntityChange> {
    private FriendshipRequestDbRepository friendshipRequestDbRepository;
    private List<Observer<RequestEntityChange>> observers = new ArrayList<>();

    public FriendshipRequestService(FriendshipRequestDbRepository friendshipRequestDbRepository) {
        this.friendshipRequestDbRepository = friendshipRequestDbRepository;
    }

    public void sendRequest(Long ID1, Long ID2) {
        FriendshipRequest friendshipRequest = new FriendshipRequest(ID1, ID2);

        FriendshipRequest a=friendshipRequestDbRepository.save(friendshipRequest).orElse(null);
        RequestEntityChange event = new RequestEntityChange(ChangeEventType.ADD, a);
        notifyObservers(event);
    }

    public void acceptRequest(Long ID1, Long ID2) {
        Iterable<FriendshipRequest> requests = friendshipRequestDbRepository.findAll();
        for (FriendshipRequest request : requests) {
            if (request.getId_user1().equals(ID1) && request.getId_user2().equals(ID2)) {
                request.setStatus("ACCEPTED");
                FriendshipRequest a=friendshipRequestDbRepository.update(request).orElse(null);
                RequestEntityChange event = new RequestEntityChange(ChangeEventType.UPDATE, a);
                notifyObservers(event);
                return;

            }
        }
    }
    public FriendshipRequest update(Long ID,Boolean seen){
        FriendshipRequest toBeUpdated = friendshipRequestDbRepository.findOne(ID).orElse(null);
        toBeUpdated.setSeen(seen);
        FriendshipRequest a = friendshipRequestDbRepository.update(toBeUpdated).orElse(null);
        RequestEntityChange event = new RequestEntityChange(ChangeEventType.UPDATE, a);
        notifyObservers(event);
        return a;
    }

    public void declineRequest(Long ID1, Long ID2) {
        Iterable<FriendshipRequest> requests = friendshipRequestDbRepository.findAll();
        for (FriendshipRequest request : requests) {
            if (request.getId_user1().equals(ID1) && request.getId_user2().equals(ID2)) {
                request.setStatus("DECLINED");
                FriendshipRequest a=friendshipRequestDbRepository.update(request).orElse(null);
                RequestEntityChange event = new RequestEntityChange(ChangeEventType.UPDATE, a);
                notifyObservers(event);
                return;

            }
        }
    }

    public FriendshipRequest delete(Long ID) {
        return friendshipRequestDbRepository.delete(ID).orElse(null);
    }

    public Iterable<FriendshipRequest> findAll() {
        return friendshipRequestDbRepository.findAll();
    }

    public void update(Long ID1, Long ID2, String status) {
        FriendshipRequest friendshipRequest = new FriendshipRequest(ID1, ID2);
        friendshipRequest.setStatus(status);
        FriendshipRequest a=friendshipRequestDbRepository.update(friendshipRequest).orElse(null);
        RequestEntityChange event = new RequestEntityChange(ChangeEventType.UPDATE, a);
        notifyObservers(event);
        return;
    }

    public ArrayList<FriendshipRequest> findByReceiver(Long ID) {
        ArrayList<FriendshipRequest> friendshipRequests = new ArrayList<>();
        Iterable<FriendshipRequest> requests = friendshipRequestDbRepository.findAll();
        for (FriendshipRequest request : requests) {
            if (request.getReceiver().equals(ID)) {
                friendshipRequests.add(request);
            }
        }
        return friendshipRequests;
    }

    public FriendshipRequest findByIDs(Long ID, Long ID2) {
        Iterable<FriendshipRequest> requests = friendshipRequestDbRepository.findAll();
        for (FriendshipRequest request : requests) {
            if (request.getReceiver().equals(ID) && request.getSender().equals(ID2)) {
                return request;
            }
            if (request.getReceiver().equals(ID2) && request.getSender().equals(ID)) {
                return request;
            }
        }
        return null;
    }

    public void removeAllByID(Long ID) {
        Iterable<FriendshipRequest> requests = friendshipRequestDbRepository.findAll();
        for (FriendshipRequest request : requests) {
            if (request.getReceiver().equals(ID) || request.getSender().equals(ID)) {
                friendshipRequestDbRepository.delete(request.getID());
            }
        }
    }
    public int getNoNewRequest(Long ID){
        int num = 0;
        ArrayList<FriendshipRequest> all=findByReceiver(ID);
        for(FriendshipRequest friendshipRequest:all){
            if(!friendshipRequest.isSeen()){
                num++;
            }
        }
        return num;
    }
    @Override
    public void addObserver(Observer<RequestEntityChange> e) {
        observers.add(e);

    }

    @Override
    public void removeObserver(Observer<RequestEntityChange> e) {
        //observers.remove(e);
    }

    @Override
    public void notifyObservers(RequestEntityChange t) {

        observers.stream().forEach(x -> x.update(t));
    }


}
