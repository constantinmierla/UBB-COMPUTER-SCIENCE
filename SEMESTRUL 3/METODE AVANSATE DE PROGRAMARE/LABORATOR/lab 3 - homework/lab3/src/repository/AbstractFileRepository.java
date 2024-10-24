package repository;

import domain.Entity;
import domain.validators.Validator;

import java.io.*;
import java.util.*;

/**
 * Abstract repository implementation for managing entities stored in a file.
 * Extends the `InMemoryRepository` and adds functionality for file I/O operations.
 *
 * @param <ID> - the type of the entity's ID
 * @param <E>  - the type of the entity that extends `Entity<ID>`
 */
public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E> {

    // The name of the file where data is stored
    String filename;

    /**
     * Constructor that initializes the repository with a file and a validator.
     * It loads the data from the file into memory.
     *
     * @param filename  - the name of the file used for storing entities
     * @param validator - the validator for validating the entities
     */
    public AbstractFileRepository(String filename, Validator<E> validator) {
        super(validator);
        this.filename = filename;
        loadData();
    }

    /**
     * Loads data from the file into memory (the repository).
     * Reads each line of the file, splits it into attributes, and creates entities to be stored in memory.
     */
    private void loadData() {
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String newLine;
            // Read each line from the file
            while ((newLine = reader.readLine()) != null) {
                System.out.println(newLine);
                List<String> data = Arrays.asList(newLine.split(";"));  // Split line into attributes
                E entity = extractEntity(data);  // Create entity from attributes
                super.save(entity);  // Save entity in memory
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();  // Handle file not found exception
        } catch (IOException e) {
            e.printStackTrace();  // Handle general I/O exceptions
        }
    }

    /**
     * Abstract method to be implemented by subclasses for extracting an entity from a list of attributes.
     * Each subclass will define how to interpret the data based on the entity type.
     *
     * @param attributes - list of attributes extracted from the file
     * @return E - the entity created from the attributes
     */
    public abstract E extractEntity(List<String> attributes);

    /**
     * Abstract method to be implemented by subclasses for converting an entity into a string format.
     * This string will be used for writing the entity back to the file.
     *
     * @param entity - the entity to be converted to string
     * @return String - the string representation of the entity
     */
    protected abstract String createEntityAsString(E entity);

    /**
     * Saves an entity in memory and writes it to the file.
     * If the entity is successfully saved in memory (i.e., it's new), it is also appended to the file.
     *
     * @param entity - the entity to be saved
     * @return E - the entity if it already exists, null if it was saved successfully
     */
    @Override
    public E save(E entity) {
        E result = super.save(entity);  // Save in memory first
        if (result == null)  // If save was successful, write to file
            writeToFile(entity);
        return result;
    }

    /**
     * Writes the given entity to the file by appending it.
     *
     * @param entity - the entity to be written to the file
     */
    protected void writeToFile(E entity) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filename, true))) {
            writer.write(createEntityAsString(entity));  // Convert entity to string
            writer.newLine();  // Add a new line after the entity
        } catch (FileNotFoundException e) {
            e.printStackTrace();  // Handle file not found exception
        } catch (IOException e) {
            e.printStackTrace();  // Handle general I/O exceptions
        }
    }
}
