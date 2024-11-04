package ubb.scs.map.repository;

import ubb.scs.map.domain.Utilizator;
import ubb.scs.map.domain.validators.Validator;

/**
 * Repository for `Utilizator` entities with file storage. Extends `AbstractFileRepository`
 * and provides functionality to parse `Utilizator` entities from file lines and write them back.
 */
public class UtilizatorRepository extends AbstractFileRepository<Long, Utilizator> {
    /**
     * Constructs a UtilizatorRepository with the specified validator and filename.
     *
     * @param validator the validator for validating `Utilizator` entities
     * @param fileName the name of the file for data storage
     */
    public UtilizatorRepository(Validator<Utilizator> validator, String fileName) {
        super(validator, fileName);
    }

    /**
     * Parses a line from the file into a `Utilizator` entity.
     *
     * @param line the line representing the `Utilizator` data
     * @return the `Utilizator` entity represented by the line
     */
    @Override
    public Utilizator lineToEntity(String line) {
        String[] splited = line.split(";");
        Utilizator u = new Utilizator(splited[1], splited[2]);
        u.setId(Long.parseLong(splited[0]));

        return u;
    }

    /**
     * Converts a `Utilizator` entity into a line for file storage.
     *
     * @param entity the `Utilizator` entity to convert
     * @return a line representing the `Utilizator` entity data
     */
    @Override
    public String entityToLine(Utilizator entity) {
        return entity.getId() + ";" + entity.getFirstName() + ";" + entity.getLastName();
    }
}
