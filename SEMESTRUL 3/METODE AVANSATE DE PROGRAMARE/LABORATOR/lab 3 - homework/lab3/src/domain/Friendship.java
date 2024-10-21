package domain;

import java.time.LocalDateTime;

import static java.lang.Math.max;
import static java.lang.Math.min;

/**
 * This class models a Friendship entity between two users, identified by their user IDs.
 * It extends the base class `Entity<Long>`, adding attributes for the friendship date and user IDs.
 */
public class Friendship extends Entity<Long> {

    // The date when the friendship was established
    LocalDateTime date;

    // IDs of the two users involved in the friendship
    Long idUser1;
    Long idUser2;

    /**
     * Constructor that initializes a friendship between two users by their IDs.
     * The IDs are stored in a way that idUser1 is always the smaller of the two.
     *
     * @param idUser1 - ID of the first user
     * @param idUser2 - ID of the second user
     */
    public Friendship(Long idUser1, Long idUser2) {
        // Ensure idUser1 is the smaller ID and idUser2 is the larger one
        this.idUser1 = min(idUser1, idUser2);
        this.idUser2 = max(idUser1, idUser2);
    }

    /**
     * Returns the date when the friendship was created.
     *
     * @return LocalDateTime - the date of the friendship
     */
    public LocalDateTime getDate() {
        return date;
    }

    /**
     * Returns the ID of the first user in the friendship.
     *
     * @return Long - the ID of the first user
     */
    public Long getIdUser1() {
        return idUser1;
    }

    /**
     * Returns the ID of the second user in the friendship.
     *
     * @return Long - the ID of the second user
     */
    public Long getIdUser2() {
        return idUser2;
    }
}
