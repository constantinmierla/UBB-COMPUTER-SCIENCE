package org.example.socialnetworkfx.socialnetworkfx.service;

import org.example.socialnetworkfx.socialnetworkfx.domain.FriendshipRequest;
import org.example.socialnetworkfx.socialnetworkfx.domain.RequestStatus;
import org.example.socialnetworkfx.socialnetworkfx.repository.FriendshipRequestDbRepository;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Iterator;

public class FriendshipRequestService implements Service<FriendshipRequest> {
    private FriendshipRequestDbRepository friendshipRequestDbRepository;
    public FriendshipRequestService(FriendshipRequestDbRepository friendshipRequestDbRepository) {
        this.friendshipRequestDbRepository = friendshipRequestDbRepository;
    }
    public void sendRequest(Long ID1,Long ID2){
        FriendshipRequest friendshipRequest = new FriendshipRequest(ID1,ID2);

        friendshipRequestDbRepository.save(friendshipRequest);
    }
    public void acceptRequest(Long ID1,Long ID2){
        Iterable<FriendshipRequest> requests=friendshipRequestDbRepository.findAll();
        for(FriendshipRequest request:requests){
            if(request.getId_user1().equals(ID1) && request.getId_user2().equals(ID2)){
                request.setStatus("ACCEPTED");
                friendshipRequestDbRepository.update(request);

            }
        }
    }
    public void declineRequest(Long ID1,Long ID2){
        Iterable<FriendshipRequest> requests=friendshipRequestDbRepository.findAll();
        for(FriendshipRequest request:requests){
            if(request.getId_user1().equals(ID1) && request.getId_user2().equals(ID2)){
                request.setStatus("DECLINED");
                friendshipRequestDbRepository.update(request);

            }
        }
    }
    public FriendshipRequest delete(Long ID){
        return friendshipRequestDbRepository.delete(ID).orElse(null);
    }
    public Iterable<FriendshipRequest> findAll(){
        return friendshipRequestDbRepository.findAll();
    }
    public void update(Long ID1,Long ID2,String status){
        FriendshipRequest friendshipRequest = new FriendshipRequest(ID1,ID2);
        friendshipRequest.setStatus(status);
        friendshipRequestDbRepository.update(friendshipRequest);
    }

    public ArrayList<FriendshipRequest> findByReceiver(Long ID) {
        ArrayList<FriendshipRequest> friendshipRequests = new ArrayList<>();
        Iterable<FriendshipRequest> requests=friendshipRequestDbRepository.findAll();
        for(FriendshipRequest request:requests){
            if(request.getReceiver().equals(ID)){
                friendshipRequests.add(request);
            }
        }
        return friendshipRequests;
    }
    public FriendshipRequest findByIDs(Long ID,Long ID2) {
        Iterable<FriendshipRequest> requests=friendshipRequestDbRepository.findAll();
        for(FriendshipRequest request:requests){
            if(request.getReceiver().equals(ID) && request.getSender().equals(ID2)){
                return request;
            }
            if(request.getReceiver().equals(ID2) && request.getSender().equals(ID)){
                return request;
            }
        }
        return null;
    }



}
