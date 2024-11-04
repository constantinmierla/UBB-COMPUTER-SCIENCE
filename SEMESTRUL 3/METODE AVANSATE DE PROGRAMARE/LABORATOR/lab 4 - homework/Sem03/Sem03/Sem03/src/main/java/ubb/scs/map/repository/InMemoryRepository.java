package ubb.scs.map.repository;


import ubb.scs.map.domain.Entity;
import ubb.scs.map.domain.validators.ValidationException;
import ubb.scs.map.domain.validators.Validator;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

/**
 * In-memory storage for entities, providing basic CRUD operations.
 *
 * @param <ID> the type of the ID used for each entity
 * @param <E> the type of entity being managed
 */
public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID,E> {
    private Validator<E> validator;
    protected Map<ID,E> entities;

    /**
     * Constructs an InMemoryRepository with a specified validator.
     *
     * @param validator the validator used to validate entities before saving or updating
     */
    public InMemoryRepository(Validator<E> validator) {
        this.validator = validator;
        entities = new HashMap<>();
    }

    /**
     * Finds an entity by ID.
     *
     * @param id the ID of the entity to retrieve
     * @return the entity with the specified ID, or null if it doesn't exist
     */
    @Override
    public Optional<E> findOne(ID id) {
        if (id == null)
            throw new IllegalArgumentException("id must be not null");
        return Optional.ofNullable(entities.get(id));
    }

    /**
     * Retrieves all entities.
     *
     * @return an iterable collection of all entities
     */
    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }

    /**
     * Saves a new entity.
     *
     * @param entity the entity to save
     * @return null if saved successfully, or the existing entity if already present
     * @throws ValidationException if the entity fails validation
     */
    @Override
    public Optional<E> save(E entity) throws ValidationException {
        if (entity == null)
            throw new IllegalArgumentException("entity must be not null");
        validator.validate(entities.values(), entity);
        return Optional.ofNullable(entities.putIfAbsent(entity.getId(), entity));

    }

    /**
     * Deletes an entity by ID.
     *
     * @param id the ID of the entity to delete
     * @return the deleted entity, or null if it was not found
     */
    @Override
    public Optional<E> delete(ID id) {
        if (id == null)
            throw new IllegalArgumentException("id must be not null");
        return Optional.ofNullable(entities.remove(id));
    }

    /**
     * Updates an existing entity.
     *
     * @param entity the entity to update
     * @return null if updated successfully, or the entity itself if it does not exist
     */
    @Override
    public Optional<E> update(E entity) {
        if (entity == null)
            throw new IllegalArgumentException("entity must be not null!");
        validator.validate(entities.values(), entity);
        if (entities.get(entity.getId()) != null) {
            entities.put(entity.getId(), entity);
            return null;
        }
        return Optional.ofNullable(entity);
    }
}
