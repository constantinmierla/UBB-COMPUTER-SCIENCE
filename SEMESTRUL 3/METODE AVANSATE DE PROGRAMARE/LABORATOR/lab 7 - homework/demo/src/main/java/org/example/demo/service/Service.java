package org.example.service;

/**
 * Service interface for generic entities
 * This interface can be implemented by any service class managing entities
 * @param <E> the type of entity managed by the service
 */
public interface Service<E> {
    /**
     * Generates a unique ID for an entity
     * @return a unique ID of type {@link Long}
     */
    Long generateID();
}