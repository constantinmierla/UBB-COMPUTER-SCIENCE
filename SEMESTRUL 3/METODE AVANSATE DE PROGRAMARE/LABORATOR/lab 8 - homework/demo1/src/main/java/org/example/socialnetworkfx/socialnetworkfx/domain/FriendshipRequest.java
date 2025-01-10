package org.example.socialnetworkfx.socialnetworkfx.domain;

import java.time.LocalDateTime;

public class FriendshipRequest extends Entity<Long> {
    private Long sender;
    private Long receiver;
    LocalDateTime timeSend;
    private String status;
    private boolean seen;

    @Override
    public String toString() {
        return "FriendshipRequest{" +
                "sender=" + sender +
                ", receiver=" + receiver +
                ", timeSend=" + timeSend +
                ", status='" + status + '\'' +
                ", seen=" + seen +
                '}';
    }

    public FriendshipRequest(Long userID1, Long userID2) {
        this.sender = userID1;
        this.receiver = userID2;
        this.timeSend = LocalDateTime.now();
        this.seen = false;
    }

    public String getDatefrom() {
        return timeSend.toString();
    }

    public Long getId_user1() {
        return sender;
    }

    public void setId_user1(Long id_user1) {
        this.sender = id_user1;
    }

    public Long getId_user2() {
        return receiver;
    }

    public Long getSender() {
        return sender;
    }

    public void setSender(Long sender) {
        this.sender = sender;
    }

    public Long getReceiver() {
        return receiver;
    }

    public void setReceiver(Long receiver) {
        this.receiver = receiver;
    }

    public LocalDateTime getTimeSend() {
        return timeSend;
    }

    public void setTimeSend(LocalDateTime timeSend) {
        this.timeSend = timeSend;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public boolean isSeen() {
        return seen;
    }

    public void setSeen(boolean seen) {
        this.seen = seen;
    }
}
