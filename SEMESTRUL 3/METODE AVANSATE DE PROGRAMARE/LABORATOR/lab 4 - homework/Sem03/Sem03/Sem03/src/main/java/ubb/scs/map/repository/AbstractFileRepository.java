package ubb.scs.map.repository;

import ubb.scs.map.domain.Entity;
import ubb.scs.map.domain.validators.Validator;

import java.io.*;
import java.util.Optional;

/**
 * Abstract repository for handling entities with file storage. Extends `InMemoryRepository`
 * and includes functionality for loading from and writing to a file.
 *
 * @param <ID> the type of the entity ID
 * @param <E> the type of the entity
 */
public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E>{
    private String filename;

    /**
     * Constructs an AbstractFileRepository with the specified validator and filename.
     *
     * @param validator the validator for validating entities
     * @param fileName the name of the file for data storage
     */
    public AbstractFileRepository(Validator<E> validator, String fileName) {
        super(validator);
        filename=fileName;
        loadData();
    }

    /**
     * Converts a line from the file into an entity.
     *
     * @param line the line representing the entity data
     * @return the entity represented by the line
     */
    public abstract E lineToEntity(String line);

    /**
     * Converts an entity into a line for file storage.
     *
     * @param entity the entity to convert
     * @return a line representing the entity data
     */
    public abstract String entityToLine(E entity);

    /**
     * Saves an entity and writes the updated data to the file.
     *
     * @param entity the entity to save
     * @return null if saved successfully, or the existing entity if already present
     */
    @Override
    public Optional<E> save(E entity) {
        Optional<E> e = super.save(entity);
        if (e.isEmpty())
            writeToFile();
        return e;
    }

    /**
     * Writes all entities to the file.
     */
    private void writeToFile() {
        try( BufferedWriter writer = new BufferedWriter(new FileWriter(filename))){
            entities.values().forEach(entity -> {
                try{
                    writer.write(entityToLine(entity));
                    writer.newLine();
                }catch(IOException e){
                    throw new RuntimeException("Error writing entity to file: "+ entity, e);
                }
            });
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }

    /**
     * Deletes an entity by ID and writes the updated data to the file.
     *
     * @param id the ID of the entity to delete
     * @return the deleted entity, or null if it was not found
     */
    @Override
    public Optional<E> delete(ID id) {
        Optional<E> e=super.delete(id);
        if (e.isPresent())
            writeToFile();
        return e;
    }

    /**
     * Updates an entity and writes the updated data to the file.
     *
     * @param entity the entity to update
     * @return null if updated successfully, or the entity itself if it does not exist
     */
    @Override
    public Optional<E> update(E entity) {
        Optional<E> e=super.update(entity);
        if (e==null)
            writeToFile();
        return e;
    }

    /**
     * Loads all entities from the file into the repository.
     */
    private void loadData() {
        try(BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = reader.readLine()) != null) {
                E entity=lineToEntity(line);
                entities.put(entity.getId(), entity);
            }
        }
        catch (IOException e)
        {
            throw new RuntimeException(e);
        }
    }

    /**
     * Appends a single entity to the file.
     *
     * @param entity the entity to append
     */
    private void appendToFile(E entity) {

        try  ( BufferedWriter writer = new BufferedWriter(new FileWriter(filename, true)))
        {
            String ent = entityToLine(entity);
            writer.write(ent);
            writer.newLine();
        }
        catch (IOException e)
        {
            throw new RuntimeException(e);
        }
    }
}
