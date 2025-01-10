package org.example.socialnetworkfx.socialnetworkfx.repository;

import org.example.socialnetworkfx.socialnetworkfx.domain.User;
import org.example.socialnetworkfx.socialnetworkfx.domain.validation.Validation;
import org.example.socialnetworkfx.socialnetworkfx.domain.validation.ValidationException;

import java.sql.*;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class UserDbRepository extends AbstractDbRepository<Long, User> {
    public UserDbRepository(String url,String username,String password,Validation<User> validator) {
        super(url,username,password,validator);
    }
    @Override
    public Optional<User> findOne(Long id) {
        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(), getPassword())) {
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM \"User\" WHERE id_user = ?");
            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                Long ID1 = resultSet.getLong("id_user");
                String firstName1 = resultSet.getString("firstname");
                String lastName1 = resultSet.getString("lastname");
                String email1 = resultSet.getString("email");
                String password1 = resultSet.getString("password");
                User user1 = new User(firstName1, lastName1, email1, password1);
                user1.setID(ID1);
                return Optional.of(user1);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }
    @Override
    public Iterable<User> findAll() {
        Set<User> users = new HashSet<>();
        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(), getPassword());
             PreparedStatement statement = connection.prepareStatement("SELECT * from \"User\"");
            ResultSet resultSet = statement.executeQuery()){
            while (resultSet.next()) {
                Long ID1 = resultSet.getLong("id_user");
                String firstName1 = resultSet.getString("firstname");
                String lastName1 = resultSet.getString("lastname");
                String email = resultSet.getString("email");
                String password = resultSet.getString("password");
                User user1 = new User(firstName1, lastName1, email, password);
                user1.setID(ID1);
                users.add(user1);
            }
            return users;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return users;
    }
    @Override
    public Optional<User> save(User entity) throws ValidationException {
        int rez = -1;
        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(), getPassword());
             PreparedStatement statement = connection.prepareStatement("INSERT INTO \"User\" (firstname,lastname,email,password) VALUES (?, ?, ?, ?)")){
            statement.setString(1, entity.getFirstName());
            statement.setString(2, entity.getLastName());
            statement.setString(3, entity.getEmail());
            statement.setString(4, entity.getPassword());
            getValidator().validate(entity);
            rez = statement.executeUpdate();
        } catch (SQLException e) {
            e.getMessage();
        }
        if (rez > 0)
            return Optional.empty();
        else
            return Optional.of(entity);
    }
    @Override
    public Optional<User> delete(Long id) {
        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(), getPassword())) {
            Optional<User> user = findOne(id);
            if (user.isEmpty()) {
                return Optional.empty();
            }
            PreparedStatement statement = connection.prepareStatement("DELETE FROM \"User\" WHERE id_user = ?");
            statement.setLong(1, id);
            int rowsAffected = statement.executeUpdate();

            if (rowsAffected > 0) {
                return user;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }
    @Override
    public Optional<User> update(User entity) {
        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(),getPassword())) {
            Optional<User> user = findOne(entity.getID());
            if (user.isEmpty()) {
                return Optional.of(entity);
            }
            //getValidator().validate(entity);
            PreparedStatement statement = connection.prepareStatement("UPDATE \"User\" SET firstname=?, lastname=?,email=?,password=? WHERE id_user = ?");
            statement.setString(1, entity.getFirstName());
            statement.setString(2, entity.getLastName());
            statement.setString(3, entity.getEmail());
            statement.setString(4, entity.getPassword());
            statement.setLong(5, entity.getID());
            int rowsAffected = statement.executeUpdate();
            if (rowsAffected > 0) {
                return Optional.of(entity);
            }
        } catch (SQLException | ValidationException e) {
            e.getMessage();
        }
        return Optional.empty();
    }
}