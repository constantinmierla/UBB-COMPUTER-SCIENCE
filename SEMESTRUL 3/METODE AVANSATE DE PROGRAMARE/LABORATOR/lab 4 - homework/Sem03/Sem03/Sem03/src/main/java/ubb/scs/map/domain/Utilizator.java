package ubb.scs.map.domain;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

/**
 * Represents a user in the system with a first name and a last name.
 * Extends the `Entity` class with a Long identifier.
 */
public class Utilizator extends Entity<Long>{
    private String firstName;
    private String lastName;

    /**
     * Constructs a new `Utilizator` entity with the specified first and last names.
     *
     * @param firstName the first name of the user
     * @param lastName  the last name of the user
     */
    public Utilizator(String firstName, String lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
    }

    /**
     * Retrieves the first name of the user.
     *
     * @return the first name
     */
    public String getFirstName() {
        return firstName;
    }

    /**
     * Sets the first name of the user.
     *
     * @param firstName the new first name
     */
    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    /**
     * Retrieves the last name of the user.
     *
     * @return the last name
     */
    public String getLastName() {
        return lastName;
    }

    /**
     * Sets the last name of the user.
     *
     * @param lastName the new last name
     */
    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    @Override
    public String toString() {
        return "ID: " + getId() + "; First Name: " + firstName + "; Last Name: " + lastName;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Utilizator)) return false;
        Utilizator that = (Utilizator) o;
        return getFirstName().equals(that.getFirstName()) &&
                getLastName().equals(that.getLastName());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getFirstName(), getLastName());
    }
}