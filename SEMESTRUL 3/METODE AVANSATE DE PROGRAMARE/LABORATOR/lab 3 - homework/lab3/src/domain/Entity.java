package domain;

import java.io.Serializable;
import java.util.Objects;

/**
 * This generic class models an entity with an identifier of type ID.
 * It implements Serializable to allow objects of this class to be serialized.
 *
 * @param <ID> - the type of the identifier for the entity (e.g., Long, String, etc.)
 */
public class Entity<ID> implements Serializable {

    // Serialization version unique identifier
    private static final long serialVersionUid = 0;

    // The identifier for the entity
    protected ID id;

    /**
     * Getter for the entity's identifier.
     *
     * @return ID - the identifier of the entity
     */
    public ID getId(){
        return id;
    }

    /**
     * Setter for the entity's identifier.
     *
     * @param id - the identifier to be set for the entity
     */
    public void setId(ID id){
        this.id = id;
    }

    /**
     * Overrides the equals method to compare entities by their ID.
     *
     * @param o - the object to compare with the current entity
     * @return boolean - true if both entities have the same ID, false otherwise
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Entity<?> entity)) return false;
        return Objects.equals(getId(), entity.getId());
    }

    /**
     * Overrides the hashCode method to generate a hash code based on the entity's ID.
     *
     * @return int - the hash code of the entity
     */
    @Override
    public int hashCode() {
        return Objects.hash(getId());
    }

    /**
     * Overrides the toString method to represent the entity as a string.
     *
     * @return String - a string representation of the entity
     */
    @Override
    public String toString() {
        return "Entity{" +
                "id=" + id +
                '}';
    }
}
