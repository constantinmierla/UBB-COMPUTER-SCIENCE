package org.example.socialnetworkfx.socialnetworkfx.repository;

import org.example.socialnetworkfx.socialnetworkfx.domain.Message;
import org.example.socialnetworkfx.socialnetworkfx.domain.validation.Validation;
import org.example.socialnetworkfx.socialnetworkfx.domain.validation.ValidationException;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class MessageDbRepository extends AbstractDbRepository<Long,Message> {
    public MessageDbRepository(String url, String username, String password, Validation<Message> validator) {
        super(url, username, password, validator);
    }
    @Override
    public Optional<Message> findOne(Long id){
        try(Connection connection= DriverManager.getConnection(getUrl(),getUsername(),getPassword())){
            PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM \"Messages\" WHERE id = ?");
            preparedStatement.setLong(1, id);
            ResultSet resultSet = preparedStatement.executeQuery();
            if(resultSet.next()) {
                Long ID2=resultSet.getLong("id");
                Long to=resultSet.getLong("to");
                Long from=resultSet.getLong("from");
                String message=resultSet.getString("text");
                LocalDateTime date=resultSet.getTimestamp("time").toLocalDateTime();
                Message m=new Message(to,from,message);
                m.setID(ID2);
                m.setTime(date);
                return Optional.of(m);
            }
        }catch(Exception e){
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Message> findAll() {
        Set<Message> all=new HashSet<>();
        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(), getPassword())) {
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM \"Messages\"");
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Long ID = resultSet.getLong("id");
                Long to=resultSet.getLong("to");
                Long from=resultSet.getLong("from");
                String message=resultSet.getString("text");
                LocalDateTime date=resultSet.getTimestamp("time").toLocalDateTime();
                Long reply = resultSet.getLong("reply");

                Message m=new Message(to,from,message);
                m.setID(ID);
                m.setTime(date);
                m.setReply(reply);
                all.add(m);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return all;
    }

    @Override
    public Optional<Message> save(Message entity) {
        int rez = -1;
        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(), getPassword());
             PreparedStatement statement = connection.prepareStatement("INSERT INTO \"Messages\" (\"to\", \"from\", \"text\", \"time\") VALUES (?,?,?,?)")
        ) {
            //getValidator().validate(entity)
            statement.setLong(1, entity.getTo());
            statement.setLong(2, entity.getFrom());
            statement.setString(3,entity.getMessage());
            statement.setTimestamp(4, Timestamp.valueOf(entity.getTime()));
            rez = statement.executeUpdate();

            return rez > 0 ? Optional.empty() : Optional.of(entity);
        } catch (SQLException | ValidationException e) {
            throw new RuntimeException("error at inserting messages in the database...");
        }
    }

    @Override
    public Optional<Message> delete(Long id2) {
        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(), getPassword())) {
            Optional<Message> message = findOne(id2);
            if (message.isEmpty()) {
                return Optional.empty();
            }
            PreparedStatement statement = connection.prepareStatement("DELETE FROM \"Messages\" WHERE id = ?");
            statement.setLong(1, id2);
            int rowsAffected = statement.executeUpdate();

            if (rowsAffected > 0) {
                return message;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Optional<Message> update(Message entity) {
        try (Connection connection = DriverManager.getConnection(getUrl(), getUsername(), getPassword())) {
            Optional<Message> message = findOne(entity.getID());
            if (message.isEmpty()) {
                return Optional.of(entity);
            }
            PreparedStatement statement = connection.prepareStatement("UPDATE \"Messages\" SET \"to\"=?, \"from\"=?, \"text\"=?, \"time\"=?,reply=? WHERE id = ? ");
            statement.setLong(1, entity.getTo());
            statement.setLong(2, entity.getFrom());
            statement.setString(3, entity.getMessage());
            statement.setTimestamp(4, Timestamp.valueOf(entity.getTime()));
            statement.setLong(5,entity.getReply());
            statement.setLong(6,entity.getID());
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
