package repository;

import domain.Entity;
import domain.validators.Validator;

import java.util.HashMap;
import java.util.Map;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    Map<ID, E> entities;
    private Validator<E> validator;

    public InMemoryRepository(Validator<E> validator) {
        this.validator = validator;
        entities = new HashMap<ID, E>();
    }

    @Override
    public E findOne(ID id) {
        if (id == null){
            throw new IllegalArgumentException("id can't be null");

        }
        return entities.get(id);
    }

    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }

    @Override
    public E save(E entity) {
        if (entity == null){
            throw new IllegalArgumentException("entity can't be null");
        }
        validator.validate(entity);
        if(entities.get(entity.getId()) != null)
        {
            return entity;
        }
        else entities.put(entity.getId(), entity);
        return null;
    }

    @Override
    public E delete(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("id can't be null");
        }
        return entities.remove(id);
    }

    @Override
    public E update(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("entity can't be null");
        }
        validator.validate(entity);
        if(entities.get(entity.getId()) != null)
        {
            entities.put(entity.getId(), entity);
            return null;
        }
        return entity;
    }
}
