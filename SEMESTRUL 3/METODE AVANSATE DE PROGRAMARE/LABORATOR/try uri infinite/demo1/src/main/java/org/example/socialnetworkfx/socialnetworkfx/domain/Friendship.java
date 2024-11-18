package org.example.socialnetworkfx.socialnetworkfx.domain;

import java.time.LocalDateTime;
import java.util.Objects;

public class Friendship extends Entity<Long> {
    private Long firstFriend;
    private Long secondFriend;
    private LocalDateTime friendsFrom;

    public Friendship(Long firstFriend, Long secondFriend) {
        this.firstFriend = firstFriend;
        this.secondFriend = secondFriend;
        this.friendsFrom = LocalDateTime.now();
    }

    public String getDatesince(){
        return friendsFrom.toString();
    }

    public Long getFirstFriend() {
        return firstFriend;
    }

    public void setFirstFriend(Long firstFriend) {
        this.firstFriend = firstFriend;
    }

    public Long getSecondFriend() {
        return secondFriend;
    }

    public void setSecondFriend(Long secondFriend) {
        this.secondFriend = secondFriend;
    }

    public LocalDateTime getFriendsFrom() {
        return friendsFrom;
    }

    public void setFriendsFrom(LocalDateTime friendsFrom) {
        this.friendsFrom = friendsFrom;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Friendship that = (Friendship) o;
        return Objects.equals(firstFriend, that.firstFriend) && Objects.equals(secondFriend, that.secondFriend) && Objects.equals(friendsFrom, that.friendsFrom);
    }

    @Override
    public int hashCode() {
        return Objects.hash(firstFriend, secondFriend, friendsFrom);
    }
}

