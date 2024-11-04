package ubb.scs.map.domain;

/**
 * Represents a base entity with a unique identifier.
 *
 * @param <ID> the type of the entity's identifier
 */
public class Entity<ID>  {
    private ID id;

    /**
     * Retrieves the unique identifier of the entity.
     *
     * @return the unique identifier of type {@code ID}
     */
    public ID getId() {
        return id;
    }

    /**
     * Sets the unique identifier for the entity.
     *
     * @param id the unique identifier to set, of type {@code ID}
     */
    public void setId(ID id) {
        this.id = id;
    }
}