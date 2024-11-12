package org.example.repository;

import org.example.domain.User;
import org.example.domain.validators.Validator;
import org.example.repository.Repository;

import java.sql.*;
import java.util.Collection;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;


public class UserDBRepository implements Repository<Long, User>{
    private final String url;
    private final String usernameDB;
    private final String passwordDB;
    private final Validator<User> userValidator;

    public UserDBRepository(String url, String usernameDB, String passwordDB, Validator<User> userValidator) {
        this.url = url;
        this.usernameDB = usernameDB;
        this.passwordDB = passwordDB;
        this.userValidator = userValidator;
    }
    /**
     * Constructs a User object from the current row in the provided ResultSet.
     *
     * @param resultSet the ResultSet positioned at the current row to retrieve User data from, must not be null.
     * @return a User object constructed from the data in the current ResultSet row.
     * @throws SQLException if an SQL error occurs while retrieving data from the ResultSet.
     */
    private User getUserFromQueryResult(ResultSet resultSet) throws SQLException{
        var id_user = resultSet.getLong("id_user");
        var firstName =resultSet.getString("firstname");
        var lastName = resultSet.getString("lastname");

        var user = new User(firstName, lastName);
        user.setId(id_user);

        return user;
    }
    /**
     * Sets parameter values in the provided PreparedStatement based on the User data.
     *
     * @param stmt the PreparedStatement to set parameter values in, must not be null.
     * @param user the User object whose data is used to set the parameters in the statement.
     * @throws SQLException if an SQL error occurs while setting parameter values in the PreparedStatement.
     */
    private void setUserDataInStatement(PreparedStatement stmt, User user) throws SQLException{
        stmt.setString(1, user.getFirstname());
        stmt.setString(2, user.getLastname());
    }

    /**
     * Finds a user by their unique ID in the database.
     *
     * @param id the ID of the user to find, must not be null.
     * @return an `Optional<User>` containing the found user if present; otherwise, an empty `Optional`.
     * @throws RuntimeException if an SQL exception occurs while attempting to connect or execute the query.
     */
    @Override
    public Optional<User> findOne(Long id) {
        String sql = "SELECT * FROM \"users\" WHERE id_user = ?";
        try(Connection connection = DriverManager.getConnection(this.url, this.usernameDB, this.passwordDB);
            PreparedStatement statement = connection.prepareStatement(sql)){

            statement.setLong(1,id);
            ResultSet resultSet = statement.executeQuery();
            if(resultSet.next()){
                return Optional.of(getUserFromQueryResult(resultSet));
            }
            return Optional.empty();
        } catch (SQLException e){
            throw new RuntimeException("Error - not found user in db");
        }
    }
    /**
     * Retrieves all users from the database.
     *
     * @return a `Collection<User>` containing all users in the database.
     * @throws RuntimeException if an SQL exception occurs during the connection or query execution.
     */
    public Collection<User> findAll() {
        Set<User> users = new HashSet<>();

        try(Connection connection = DriverManager.getConnection(this.url, this.usernameDB, this.passwordDB);
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM \"users\"");
            ResultSet resultSet = statement.executeQuery()){

            while(resultSet.next()) {
                var user = getUserFromQueryResult(resultSet);
                users.add(user);
            }

            return users;
        }
        catch (SQLException e) {
            throw new RuntimeException("Error - not found users in db");
        }
    }
    /**
     * Saves a new user to the database.
     *
     * @param user The {@link User} object to save.
     * @return An {@link Optional} containing the {@code User} if the insertion fails, or {@link Optional#empty()} if the insertion is successful.
     * @throws RuntimeException If a database access error occurs or the SQL statement is invalid.
     */
    @Override
    public Optional<User> save(User user) {
        this.userValidator.validate(this.findAll(), user);

        String sql = "INSERT INTO \"users\" (firstname, lastname) VALUES (?, ?)";
        try(Connection connection = DriverManager.getConnection(this.url, this.usernameDB, this.passwordDB);
            PreparedStatement statement = connection.prepareStatement(sql)){
            this.setUserDataInStatement(statement, user);

            return statement.executeUpdate() > 0 ? Optional.empty() : Optional.of(user);
        } catch (SQLException e){
            throw new RuntimeException("Error - not saved user in db");
        }
    }
    /**
     * Deletes a user by their unique ID from the database.
     *
     * @param id the ID of the user to delete, must not be null.
     * @return an `Optional<User>` containing the deleted user if the deletion was successful; otherwise, an empty `Optional`.
     * @throws RuntimeException if an SQL exception occurs during the connection or query execution.
     */
    @Override
    public Optional<User> delete(Long id) {
        String sql = "DELETE FROM \"users\" WHERE id_user = ?";
        try(Connection connection = DriverManager.getConnection(this.url, this.usernameDB, this.passwordDB)) {
            var user = this.findOne(id);
            if(user.isEmpty())
                return Optional.empty();

            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setLong(1, id);

            return statement.executeUpdate() > 0 ? user : Optional.empty();
        }
        catch (SQLException e) {
            throw new RuntimeException("Error - not deleted user from db");
        }
    }
    /**
     * Updates an existing user's details in the database.
     *
     * @param user the user with updated details; must not be null and should have a valid ID.
     * @return an `Optional<User>` containing the updated user if the update was successful; otherwise, an empty `Optional` if the user was not found.
     * @throws RuntimeException if an SQL exception occurs during connection or query execution.
     */
    @Override
    public Optional<User> update(User user) {
        if (this.findOne(user.getId()).isEmpty()) {
            return Optional.empty();
        }

        String sql = "UPDATE \"Users\" SET firstname = ?, lastname = ? WHERE id_user = ?";

        try (Connection connection = DriverManager.getConnection(this.url, this.usernameDB, this.passwordDB);
             PreparedStatement statement = connection.prepareStatement(sql)) {

            this.setUserDataInStatement(statement, user);
            statement.setLong(3, user.getId());

            return statement.executeUpdate() > 0 ? Optional.of(user) : Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException("Error - not updated user in db", e);
        }
    }
}
