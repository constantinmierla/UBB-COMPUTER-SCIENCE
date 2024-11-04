package ubb.scs.map.repository;

import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Utilizator;
import ubb.scs.map.domain.validators.Validator;

/**
 * Repository for `Friendship` entities with file storage. Extends `AbstractFileRepository`
 * and provides functionality to parse `Friendship` entities from file lines and write them back.
 */
public class FriendshipRepository extends AbstractFileRepository<Long, Friendship> {
    /**
     * Constructs a FriendshipRepository with the specified validator and filename.
     *
     * @param validator the validator for validating `Friendship` entities
     * @param filename the name of the file for data storage
     */
    public FriendshipRepository(Validator<Friendship> validator, String filename) {
        super(validator, filename);
    }

    /**
     * Parses a line from the file into a `Friendship` entity.
     *
     * @param line the line representing the `Friendship` data in the format
     *             id_prietenie;id_u1;nume_u1;prenume_u1;id_u2;nume_u2;prenume_u2
     * @return the `Friendship` entity represented by the line
     */
    @Override
    public Friendship lineToEntity(String line) {
        //id_prietenie;id_u1;nume_u1;prenume_u1;id_u2;nume_u2;prenume_u2
        String[] fields = line.split(";");
        Long idFriendship = Long.parseLong(fields[0]);

        Long id = Long.parseLong(fields[1]);
        String firstname = fields[2];
        String lastname = fields[3];

        var u = new Utilizator(firstname, lastname);
        u.setId(id);

        Long id2 = Long.parseLong(fields[4]);
        String firstname2 = fields[5];
        String lastname2 = fields[6];

        var u2 = new Utilizator(firstname2, lastname2);
        u2.setId(id2);

        Friendship friendship = new Friendship(u, u2);
        friendship.setId(idFriendship);

        return friendship;
    }

    /**
     * Converts a `Friendship` entity into a line for file storage.
     *
     * @param entity the `Friendship` entity to convert
     * @return a line representing the `Friendship` entity data
     */
    @Override
    public String entityToLine(Friendship entity) {
        String sb = entity.getId() + ";";

        sb += entity.getFirstUser().getId() + ";" + entity.getFirstUser().getFirstName() + ";" +
                entity.getFirstUser().getLastName() + ";";

        sb += entity.getSecondUser().getId() + ";" + entity.getSecondUser().getFirstName() + ";" +
                entity.getSecondUser().getLastName();

        return sb;
    }
}
