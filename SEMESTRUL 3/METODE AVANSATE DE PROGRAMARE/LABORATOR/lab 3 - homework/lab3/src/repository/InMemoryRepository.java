package repository;

import domain.Entity;
import domain.validators.Validator;

import java.util.HashMap;
import java.util.Map;

/**
 * InMemoryRepository is a generic implementation of a repository that stores entities in memory using a HashMap.
 *
 * @param <ID> - the type of the entity identifier
 * @param <E> - the type of the entity, which extends Entity<ID>
 */
public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    Map<ID, E> entities;         // The map storing entities with their corresponding IDs
    private Validator<E> validator;  // Validator for entity validation

    /**
     * Constructor that initializes the repository with a given validator.
     *
     * @param validator - the validator used to check the validity of the entities
     */
    public InMemoryRepository(Validator<E> validator) {
        this.validator = validator;
        entities = new HashMap<>();  // Initialize the HashMap to store entities
    }

    /**
     * Finds an entity by its ID.
     *
     * @param id - the ID of the entity to find
     * @return the entity with the given ID, or null if not found
     * @throws IllegalArgumentException if the provided ID is null
     */
    @Override
    public E findOne(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("id can't be null");
        }
        return entities.get(id);  // Return the entity corresponding to the given ID
    }

    /**
     * Finds all entities stored in the repository.
     *
     * @return an iterable collection of all entities
     */
    @Override
    public Iterable<E> findAll() {
        return entities.values();  // Return all entities stored in the map
    }

    /**
     * Saves an entity to the repository after validating it.
     * If an entity with the same ID already exists, it returns the existing entity, otherwise it adds the new entity.
     *
     * @param entity - the entity to save
     * @return null if the entity is successfully added, or the existing entity if the ID is already used
     * @throws IllegalArgumentException if the provided entity is null
     */
    @Override
    public E save(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("entity can't be null");
        }
        validator.validate(entity);  // Validate the entity before saving
        if (entities.get(entity.getId()) != null) {
            return entity;  // If the entity already exists, return it
        } else {
            entities.put(entity.getId(), entity);  // Otherwise, add the new entity
        }
        return null;
    }

    /**
     * Deletes an entity from the repository by its ID.
     *
     * @param id - the ID of the entity to delete
     * @return the deleted entity, or null if the entity does not exist
     * @throws IllegalArgumentException if the provided ID is null
     */
    @Override
    public E delete(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("id can't be null");
        }
        return entities.remove(id);  // Remove the entity by ID and return the removed entity
    }

    /**
     * Updates an existing entity in the repository after validating it.
     * If the entity does not exist, it returns the entity without updating.
     *
     * @param entity - the entity to update
     * @return null if the entity is successfully updated, or the entity itself if it does not exist in the repository
     * @throws IllegalArgumentException if the provided entity is null
     */
    @Override
    public E update(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("entity can't be null");
        }
        validator.validate(entity);  // Validate the entity before updating
        if (entities.get(entity.getId()) != null) {
            entities.put(entity.getId(), entity);  // Update the entity if it exists
            return null;
        }
        return entity;  // Return the entity if it does not exist in the repository
    }
}
