package domain;

import java.util.*;

/**
 * Represents a user in the social network, with a first name, last name, and a list of friends.
 * Inherits from the generic Entity class with Long as the type of the identifier.
 */
public class User extends Entity<Long> {
    private String firstname; // The first name of the user
    private String lastname;  // The last name of the user
    List<User> friends;       // List of friends (other User objects)

    /**
     * Constructs a new User with the given first name and last name.
     *
     * @param firstname - the user's first name
     * @param lastname - the user's last name
     */
    public User(String firstname, String lastname) {
        this.firstname = firstname;
        this.lastname = lastname;
        friends = new Vector<>(); // Initialize the list of friends as a Vector
    }

    /**
     * Adds a friend to the user's friend list.
     *
     * @param user - the user to add as a friend
     */
    public void addFriend(User user) {
        friends.add(user);
    }

    /**
     * Removes a friend from the user's friend list.
     *
     * @param user - the user to remove from the friend list
     */
    public void removeFriend(User user) {
        friends.remove(user);
    }

    /**
     * Gets the user's first name.
     *
     * @return the first name of the user
     */
    public String getFirstname() {
        return firstname;
    }

    /**
     * Sets the user's first name.
     *
     * @param firstname - the new first name of the user
     */
    public void setFirstname(String firstname) {
        this.firstname = firstname;
    }

    /**
     * Gets the user's last name.
     *
     * @return the last name of the user
     */
    public String getLastname() {
        return lastname;
    }

    /**
     * Sets the user's last name.
     *
     * @param lastname - the new last name of the user
     */
    public void setLastname(String lastname) {
        this.lastname = lastname;
    }

    /**
     * Gets the list of friends for this user.
     *
     * @return a list of users representing the user's friends
     */
    public List<User> getFriends() {
        return friends;
    }

    /**
     * Sets the list of friends for this user.
     *
     * @param friends - the list of friends to set
     */
    public void setFriends(List<User> friends) {
        this.friends = friends;
    }

    /**
     * Checks if this user is equal to another object based on ID, first name, last name, and friends list.
     *
     * @param o - the object to compare with
     * @return true if the users are the same, false otherwise
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true; // Check for reference equality
        if (o == null || getClass() != o.getClass()) return false; // Check for class type
        if (!super.equals(o)) return false; // Check ID equality (inherited)
        User user = (User) o;
        return Objects.equals(firstname, user.firstname) &&
                Objects.equals(lastname, user.lastname) &&
                Objects.equals(friends, user.friends); // Compare first name, last name, and friends list
    }

    /**
     * Generates a hash code for the user based on ID, first name, last name, and friends.
     *
     * @return the hash code of the user
     */
    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), firstname, lastname, friends); // Generate hash using the superclass hash and other fields
    }

    /**
     * Returns a string representation of the user, including first name, last name, and the friends list.
     *
     * @return a string representation of the user
     */
    @Override
    public String toString() {
        return "User{" +
                "firstname='" + firstname + '\'' +
                ", lastname='" + lastname + '\'' +
                ", friends=" + friends +
                '}'; // Provide a string representation with the user's details
    }
}
