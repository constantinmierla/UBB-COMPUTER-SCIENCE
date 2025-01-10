package org.example.demo.domain;

import java.time.LocalDateTime;
import java.util.Objects;

/**
 * Represents a friendship between two users in the system.
 * Extends the `Entity` class with a Long identifier.
 */
public class Friendship extends Entity<Long> {
    private final User user1;
    private final User user2;
    private final LocalDateTime friendsFrom;

    /**
     * Constructs a Friendship object.
     *
     * @param user1       The first user in the friendship.
     * @param user2       The second user in the friendship.
     * @param friendsFrom The date and time when the friendship started.
     */
    public Friendship(User user1, User user2, LocalDateTime friendsFrom) {
        this.user1 = user1;
        this.user2 = user2;
        this.friendsFrom = friendsFrom;
    }

    public User getFirstUser() {
        return user1;
    }

    public User getSecondUser() {
        return user2;
    }

    public LocalDateTime getFriendsFrom() {
        return friendsFrom;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Friendship that = (Friendship) o;
        return Objects.equals(user1, that.user1) &&
                Objects.equals(user2, that.user2) &&
                Objects.equals(friendsFrom, that.friendsFrom);
    }

    @Override
    public int hashCode() {
        return Objects.hash(user1, user2, friendsFrom);
    }

    @Override
    public String toString() {
        return "Friendship{" +
                "user1=" + user1 +
                ", user2=" + user2 +
                ", friendsFrom=" + friendsFrom +
                '}';
    }
}
