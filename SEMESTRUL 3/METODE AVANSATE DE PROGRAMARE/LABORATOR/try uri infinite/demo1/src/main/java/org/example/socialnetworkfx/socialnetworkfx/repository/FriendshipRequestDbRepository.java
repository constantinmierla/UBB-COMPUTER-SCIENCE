package org.example.socialnetworkfx.socialnetworkfx.repository;

import org.example.socialnetworkfx.socialnetworkfx.domain.Friendship;
import org.example.socialnetworkfx.socialnetworkfx.domain.FriendshipRequest;
import org.example.socialnetworkfx.socialnetworkfx.domain.RequestStatus;
import org.example.socialnetworkfx.socialnetworkfx.domain.User;
import org.example.socialnetworkfx.socialnetworkfx.domain.validation.Validation;
import org.example.socialnetworkfx.socialnetworkfx.domain.validation.ValidationException;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class FriendshipRequestDbRepository extends AbstractDbRepository<Long, FriendshipRequest> {
    public FriendshipRequestDbRepository(String url, String username, String password, Validation<FriendshipRequest> validator) throws SQLException {
        super(url, username, password, validator);
    }

    public Optional<FriendshipRequest> findOne(Long id) {
        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(), getPassword());) {
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM \"Friendship_request\" WHERE id= ?");
            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                Long ID1 = resultSet.getLong("id");
                Long id_user1 = resultSet.getLong("id_user1");
                Long id_user2 = resultSet.getLong("id_user2");
                String status = resultSet.getString("status");
                LocalDateTime time = resultSet.getTimestamp("datefrom").toLocalDateTime();

                FriendshipRequest request = new FriendshipRequest(id_user1, id_user2);
                request.setID(ID1);
                request.setStatus(status);
                request.setTimeSend(time);

                return Optional.of(request);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    public Iterable<FriendshipRequest> findAll() {
        Set<FriendshipRequest> friendshipRequests = new HashSet<>();

        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(), getPassword());
             PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM \"Friendship_request\" ");
             ResultSet result = preparedStatement.executeQuery()) {
            while (result.next()) {
                Long ID = result.getLong("id");
                Long id_user1 = result.getLong("id_user1");
                Long id_user2 = result.getLong("id_user2");
                String status = result.getString("status");
                LocalDateTime time = result.getTimestamp("datefrom").toLocalDateTime();
                FriendshipRequest request = new FriendshipRequest(id_user1, id_user2);
                request.setID(ID);
                request.setStatus(status);
                request.setTimeSend(time);
                friendshipRequests.add(request);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        return friendshipRequests;
    }

    public Optional<FriendshipRequest> save(FriendshipRequest entity) {
        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(), getPassword());
             PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO \"Friendship_request\" (id_user1,id_user2,status,datefrom) VALUES (?,?,?,?)"))
            {
            preparedStatement.setLong(1, entity.getSender());
            preparedStatement.setLong(2, entity.getReceiver());
            if(entity.getStatus() == null) {
                preparedStatement.setString(3, "PENDING");
            }
            else {
                preparedStatement.setString(3, entity.getStatus());
            }
            preparedStatement.setTimestamp(4, Timestamp.valueOf(entity.getTimeSend()));
            int rowsAffected = preparedStatement.executeUpdate();
            if (rowsAffected > 0) {
                return Optional.of(entity);
            }
        } catch (Exception e) {
            e.printStackTrace();

        }
        return Optional.empty();
    }

    public Optional<FriendshipRequest> delete(Long id2){
        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(), getPassword())) {
            Optional<FriendshipRequest> friendship = findOne(id2);
            if (friendship.isEmpty()) {
                return Optional.empty();
            }
            PreparedStatement statement = connection.prepareStatement("DELETE FROM \"Friendship_request\" WHERE id = ?");
            statement.setLong(1, id2);
            int rowsAffected = statement.executeUpdate();

            if (rowsAffected > 0) {
                return friendship;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    public Optional<FriendshipRequest> update(FriendshipRequest entity){
        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(), getPassword())) {
            Optional<FriendshipRequest> friendship = findOne(entity.getID());
            if (friendship.isEmpty()) {
                return Optional.of(entity);
            }
            //getValidator().validate(entity);
            PreparedStatement statement = connection.prepareStatement("UPDATE \"Friendship_request\" SET id_user1=?,id_user2=?, status=? WHERE id = ? ");
            statement.setLong(1, entity.getSender());
            statement.setLong(2, entity.getReceiver());
            statement.setString(3, entity.getStatus());
            statement.setLong(4, entity.getID());
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
