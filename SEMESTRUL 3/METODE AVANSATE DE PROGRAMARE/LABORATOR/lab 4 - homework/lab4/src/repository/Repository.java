package repository;

import domain.Entity;
import java.util.Optional;
/**
 * Interface defining basic CRUD operations
 * for a repository that manages entities of type E with an identifier of type ID.
 *
 * @param <ID> - the type of the identifier used for entities
 * @param <E>  - the type of the entities managed by the repository, which extends Entity
 */
public interface Repository<ID, E extends Entity<ID>> {

    /**
     * Finds and returns the entity with the given ID.
     *
     * @param id - the ID of the entity to be found, must not be null
     * @return E - the entity with the specified ID, or null if no such entity exists
     */
    Optional<E> findOne(ID id);

    /**
     * Returns all entities managed by the repository.
     *
     * @return Iterable<E> - a collection of all entities
     */
    Iterable<E> findAll();

    /**
     * Saves a new entity to the repository. If the entity already exists, it is not saved.
     *
     * @param entity - the entity to be saved, must not be null
     * @return E - null if the entity was successfully saved, or the existing entity if it already exists
     */
    Optional<E> save(E entity);

    /**
     * Deletes the entity with the given ID from the repository.
     *
     * @param id - the ID of the entity to be deleted, must not be null
     * @return E - the deleted entity, or null if no such entity exists
     */
    Optional<E> delete(ID id);

    /**
     * Updates an existing entity in the repository. If the entity doesn't exist, it is not updated.
     *
     * @param entity - the entity to be updated, must not be null
     * @return E - null if the entity was successfully updated, or the existing entity if it doesn't exist
     */
    Optional<E> update(E entity);
}
