package org.example.socialnetworkfx.socialnetworkfx.repository;

import org.example.socialnetworkfx.socialnetworkfx.domain.Friendship;
import org.example.socialnetworkfx.socialnetworkfx.domain.validation.Validation;
import org.example.socialnetworkfx.socialnetworkfx.domain.validation.ValidationException;
import org.example.socialnetworkfx.socialnetworkfx.utils.paging.Page;
import org.example.socialnetworkfx.socialnetworkfx.utils.paging.Pageable;

import java.sql.*;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class FriendshipDbRepository extends AbstractDbRepository<Long, Friendship> implements PagingRepository<Long, Friendship> {
    public FriendshipDbRepository(String url, String username, String password, Validation<Friendship> validator) {
        super(url, username, password, validator);
    }

    @Override
    public Optional<Friendship> findOne(Long id) {
        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(), getPassword())) {
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM \"Friendship\" WHERE id_friendship = ?");
            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                Long ID = resultSet.getLong("id_friendship");
                Long ID1 = resultSet.getLong("id_User1");
                Long ID2 = resultSet.getLong("id_User2");
                Friendship friendship = new Friendship(ID1, ID2);
                friendship.setID(ID);
                return Optional.of(friendship);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Friendship> findAll() {
        Set<Friendship> friendships = new HashSet<>();
        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(), getPassword())) {
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM \"Friendship\"");
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Long ID = resultSet.getLong("id_friendship");
                Long ID1 = resultSet.getLong("id_user1");
                Long ID2 = resultSet.getLong("id_user2");
                Friendship friendship = new Friendship(ID1, ID2);
                friendship.setID(ID);
                friendships.add(friendship);
            }
            return friendships;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return friendships;
    }

    @Override
    public Optional<Friendship> save(Friendship entity) {
        int rez = -1;
        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(), getPassword());
             PreparedStatement statement = connection.prepareStatement("INSERT INTO \"Friendship\" (id_user1,id_user2,datesince) VALUES (?,?,?)")
        ) {
            getValidator().validate(entity);
            statement.setLong(1, entity.getFirstFriend());
            statement.setLong(2, entity.getSecondFriend());
            statement.setTimestamp(3, Timestamp.valueOf(entity.getFriendsFrom()));
            rez = statement.executeUpdate();
        } catch (SQLException | ValidationException e) {
            e.getMessage();
        }
        if (rez > 0)
            return Optional.empty();
        else
            return Optional.of(entity);
    }

    @Override
    public Optional<Friendship> delete(Long id) {
        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(), getPassword())) {
            Optional<Friendship> friendship = findOne(id);
            if (friendship.isEmpty()) {
                return Optional.empty();
            }
            PreparedStatement statement = connection.prepareStatement("DELETE FROM \"Friendship\" WHERE id_friendship = ?");
            statement.setLong(1, id);
            int rowsAffected = statement.executeUpdate();

            if (rowsAffected > 0) {
                return friendship;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Optional<Friendship> update(Friendship entity) {
        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(), getPassword())) {
            Optional<Friendship> friendship = findOne(entity.getID());
            if (friendship.isEmpty()) {
                return Optional.of(entity);
            }
            getValidator().validate(entity);
            PreparedStatement statement = connection.prepareStatement("UPDATE Friendship SET id_user1=?,id_user2=?WHERE id_friendship = ? ");
            statement.setLong(1, entity.getFirstFriend());
            statement.setLong(2, entity.getSecondFriend());
            statement.setLong(3, entity.getID());
            int rowsAffected = statement.executeUpdate();
            if (rowsAffected > 0) {
                return Optional.of(entity);
            }
        } catch (SQLException | ValidationException e) {
            e.getMessage();
        }
        return Optional.empty();
    }

    @Override
    public Page<Friendship> findAllOnPage(Pageable pageable, Long id) {
        Set<Friendship> friendships = new HashSet<>();
        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(), getPassword());
             PreparedStatement pageStatement = connection.prepareStatement("SELECT * FROM \"Friendship\" WHERE id_user1=? OR id_user2=? LIMIT ? OFFSET ?");
             PreparedStatement countStatement = connection.prepareStatement("SELECT COUNT(*) AS count FROM \"Friendship\" WHERE id_user1=? OR id_user2=?")) {
            pageStatement.setLong(1, id);
            pageStatement.setLong(2, id);
            pageStatement.setInt(3, pageable.getPageSize());
            pageStatement.setInt(4, pageable.getPageNumber() * pageable.getPageSize());
            countStatement.setLong(1, id);
            countStatement.setLong(2, id);
            try (
                    ResultSet pageSet = pageStatement.executeQuery();
                    ResultSet countSet = countStatement.executeQuery()) {
                int count = 0;
                if (countSet.next()) {
                    count = countSet.getInt("count");
                }

                while (pageSet.next()) {
                    Long ID = pageSet.getLong("id_friendship");
                    Long ID1 = pageSet.getLong("id_user1");
                    Long ID2 = pageSet.getLong("id_user2");
                    Friendship friendship = new Friendship(ID1, ID2);
                    friendship.setID(ID);
                    friendships.add(friendship);
                }
                return new Page<>(friendships, count);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}

