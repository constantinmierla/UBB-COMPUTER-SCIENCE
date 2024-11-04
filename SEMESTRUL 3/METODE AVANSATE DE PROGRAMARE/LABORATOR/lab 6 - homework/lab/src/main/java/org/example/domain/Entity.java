package org.example.domain;

/**
 * Represents a base entity with a unique identifier.
 *
 * @param <ID> the type of the entity's identifier
 */
public class Entity<ID> {
    private ID id;

    public ID getId(){
        return id;
    }

    public void setId(ID id){
        this.id = id;
    }
}
