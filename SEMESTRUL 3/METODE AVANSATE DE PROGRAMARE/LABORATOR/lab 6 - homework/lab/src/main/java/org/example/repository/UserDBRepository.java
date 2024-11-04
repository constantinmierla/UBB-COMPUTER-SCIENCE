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

    private User getUserFromQueryResult(ResultSet resultSet) throws SQLException{
        var id_user = resultSet.getLong("id_user");
        var firstName =resultSet.getString("firstname");
        var lastName = resultSet.getString("lastname");

        var user = new User(firstName, lastName);
        user.setId(id_user);

        return user;
    }

    private void setUserDataInStatement(PreparedStatement stmt, User user) throws SQLException{
        stmt.setString(1, user.getFirstname());
        stmt.setString(2, user.getLastname());
    }
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
