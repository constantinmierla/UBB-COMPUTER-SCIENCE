package org.example.demo.repository;

import org.example.demo.domain.Friendship;
import org.example.demo.domain.User;
import org.example.demo.domain.validators.Validator;

import java.sql.*;
import java.util.Collection;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class FriendshipDBRepository implements Repository<Long, Friendship> {
    private final String database_url;
    private final String database_user;
    private final String database_password;
    private final Validator<Friendship> validator;

    public FriendshipDBRepository(String database_url, String database_user, String database_password, Validator<Friendship> validator) {
        this.database_url = database_url;
        this.database_user = database_user;
        this.database_password = database_password;
        this.validator = validator;
    }
    /**
     * Constructs a Friendship object from the current row in the provided ResultSet.
     *
     * @param resultSet the ResultSet positioned at the current row to retrieve Friendship data from, must not be null.
     * @return a Friendship object constructed from the data in the current ResultSet row.
     * @throws SQLException if an SQL error occurs while retrieving data from the ResultSet.
     */
    private Friendship getFriendshipFromQueryResult(ResultSet resultSet) throws SQLException {
        var id_friendship = resultSet.getLong("id");

        var idFirstUser = resultSet.getLong("firstUserID");
        var firstnameFirstUser = resultSet.getString("firstUserFirstName");
        var lastnameFirstUser = resultSet.getString("firstUserLastName");
        var user1 = new User(firstnameFirstUser, lastnameFirstUser);
        user1.setId(idFirstUser);

        var idSecondUser = resultSet.getLong("secondUserID");
        var firstnameSecondUser = resultSet.getString("secondUserFirstName");
        var lastnameSecondUser = resultSet.getString("secondUserLastName");
        var user2 = new User(firstnameSecondUser, lastnameSecondUser);
        user2.setId(idSecondUser);

        Friendship friendship = new Friendship(user1, user2);
        friendship.setId(id_friendship);

        return friendship;
    }
    /**
     * Sets parameter values in the provided PreparedStatement based on the Friendship data.
     *
     * @param statement the PreparedStatement to set parameter values in, must not be null.
     * @param friendship the Friendship object whose data is used to set the parameters in the statement.
     * @throws SQLException if an SQL error occurs while setting parameter values in the PreparedStatement.
     */
    private void setDataInStatement(PreparedStatement statement, Friendship friendship) throws SQLException {
        statement.setLong(1, friendship.getFirstUser().getId());
        statement.setString(2, friendship.getFirstUser().getFirstname());
        statement.setString(3, friendship.getFirstUser().getLastname());
        statement.setLong(4, friendship.getSecondUser().getId());
        statement.setString(5, friendship.getSecondUser().getFirstname());
        statement.setString(6, friendship.getSecondUser().getLastname());
    }

    /**
     * Finds a friendship by its unique ID in the database.
     *
     * @param id the ID of the friendship to find; must not be null.
     * @return an `Optional<Friendship>` containing the found friendship if present; otherwise, an empty `Optional`.
     * @throws RuntimeException if an SQL exception occurs while attempting to connect or execute the query.
     */

    @Override
    public Optional<Friendship> findOne(Long id) {
        String sql = "SELECT * FROM \"friendships\" WHERE id = ?";

        try (Connection connection = DriverManager.getConnection(this.database_url, this.database_user, this.database_password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {

            preparedStatement.setLong(1, id);
            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return Optional.of(this.getFriendshipFromQueryResult(resultSet));
            }
            return Optional.empty();

        } catch (SQLException e) {
            throw new RuntimeException("Eroare la gasirea prieteniei in baza de date!");
        }
    }
    /**
     * Retrieves all friendships from the database.
     *
     * @return a `Collection<Friendship>` containing all friendships; may be empty if no friendships are found.
     * @throws RuntimeException if an SQL exception occurs while attempting to connect or execute the query.
     */
    public Collection<Friendship> findAll() {
        Set<Friendship> friendships = new HashSet<>();
        String sql = "SELECT * FROM \"friendships\"";

        try (Connection connection = DriverManager.getConnection(this.database_url, this.database_user, this.database_password);
             PreparedStatement preparedStatement = connection.prepareStatement(sql);
             ResultSet resultSet = preparedStatement.executeQuery()) {

            while (resultSet.next()) {
                Friendship friendship = getFriendshipFromQueryResult(resultSet);
                friendships.add(friendship);
            }
            return friendships;

        } catch (SQLException e) {
            throw new RuntimeException("Eroare la preluarea prieteniilor din baza de date!", e);
        }
    }
    /**
     * Saves a friendship to the database.
     *
     * @param friendship the `Friendship` object to save; must not be null.
     * @return an `Optional<Friendship>` containing the saved friendship if the operation fails; otherwise, an empty `Optional`.
     * @throws RuntimeException if an SQL exception occurs while attempting to connect or execute the query.
     */
    public Optional<Friendship> save(Friendship friendship) {
        this.validator.validate(this.findAll(), friendship);

        String sql = "INSERT INTO \"friendships\" " +
                "(firstUserID, firstUserFirstName, firstUserLastName, " +
                "secondUserID, secondUserFirstName, secondUserLastName) VALUES (?, ?, ?, ?, ?, ?)";

        try (Connection connection = DriverManager.getConnection(this.database_url, this.database_user, this.database_password);
             PreparedStatement statement = connection.prepareStatement(sql)) {

            this.setDataInStatement(statement, friendship);

            return (statement.executeUpdate() > 0) ? Optional.empty() : Optional.of(friendship);

        } catch (SQLException e) {
            throw new RuntimeException("Eroare la salvarea prieteniei in baza de date!" + e.getMessage(), e);
        }
    }
    /**
     * Deletes a friendship from the database by its unique ID.
     *
     * @param id the unique ID of the friendship to be deleted, must not be null.
     * @return an `Optional<Friendship>` containing the deleted friendship if it was found and deleted successfully;
     *         otherwise, an empty `Optional`.
     * @throws RuntimeException if an SQL exception occurs while attempting to connect, execute the query, or delete the friendship.
     */
    public Optional<Friendship> delete(Long id) {
        String sql = "DELETE FROM \"friendships\" WHERE id = ?";

        try (Connection connection = DriverManager.getConnection(this.database_url, this.database_user, this.database_password);
             PreparedStatement statement = connection.prepareStatement(sql)) {

            Optional<Friendship> friendship = this.findOne(id);
            if (friendship.isEmpty()) {
                return Optional.empty();
            }

            statement.setLong(1, id);
            return statement.executeUpdate() > 0 ? friendship : Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException("Eroare la ștergerea prieteniei din baza de date!", e);
        }
    }
    /**
     * Updates the details of an existing friendship in the database.
     *
     * @param friendship the `Friendship` object containing updated details, must not be null.
     * @return an `Optional<Friendship>` containing the updated friendship if the update was successful;
     *         otherwise, an empty `Optional` if the friendship was not found.
     * @throws RuntimeException if an SQL exception occurs while attempting to connect, execute the query, or update the friendship.
     */
    public Optional<Friendship> update(Friendship friendship) {
        if(this.findOne(friendship.getId()).isEmpty()) {
            return Optional.empty();
        }

        String sql = "UPDATE \"friendships\" SET " +
                "firstUserID = ?, firstUserFirstName = ?, firstUserLastName = ?, secondUserID = ?, secondUserFirstName = ?, secondUserLastName = ?" +
                "WHERE id = ?";

        try(Connection connection = DriverManager.getConnection(this.database_url, this.database_user, this.database_password);
            PreparedStatement statement = connection.prepareStatement(sql)) {

            this.setDataInStatement(statement, friendship);
            statement.setLong(7, friendship.getId());

            return statement.executeUpdate() > 0 ? Optional.of(friendship) : Optional.empty();
        }
        catch (SQLException e) {
            throw new RuntimeException("Eroare la actualizarea prieteniei in baza de date!");
        }
    }
}
