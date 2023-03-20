package com.ubb.repository;

import com.ubb.model.User;
import com.ubb.utils.JDBCUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Optional;
import java.util.Properties;

public class UserDBRepository implements IUserRepository {
    private final JDBCUtils jdbcUtils;
    private static final Logger logger = LogManager.getLogger();

    public UserDBRepository(Properties properties) {
        logger.info("Initializing UserDBRepository with properties: {} ", properties);
        jdbcUtils = new JDBCUtils(properties);
    }

    @Override
    public Optional<User> getByUsername(String username) {
        logger.traceEntry("getByUsername with task {} ", username);
        Connection connection = jdbcUtils.getConnection();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT * FROM users WHERE username=?")) {
            preparedStatement.setString(1, username);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    User user = extract(resultSet);
                    logger.traceExit(user);
                    return Optional.of(user);
                }
            }
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
        logger.traceExit("null");
        return Optional.empty();
    }


    @Override
    public Optional<User> get(Long id) {
        logger.traceEntry();
        Connection connection = jdbcUtils.getConnection();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT * FROM users WHERE id=?")) {
            preparedStatement.setLong(1, id);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    User user = extract(resultSet);
                    logger.traceExit(user);
                    return Optional.of(user);
                }
            }
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
        logger.traceExit("null");
        return Optional.empty();
    }

    @Override
    public Collection<User> read() {
        logger.traceEntry();
        Connection connection = jdbcUtils.getConnection();
        Collection<User> users = new ArrayList<>();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT * FROM users")) {
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    User user = extract(resultSet);
                    users.add(user);
                }
            }
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
        logger.traceExit(users);
        return users;
    }

    @Override
    public void add(User newEntity) {
        logger.traceEntry("saving task {} ", newEntity);
        Connection connection = jdbcUtils.getConnection();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "INSERT INTO users (username, fullName, password) VALUES (?,?,?)")) {
            preparedStatement.setString(1, newEntity.getUsername());
            preparedStatement.setString(2, newEntity.getFullName());
            preparedStatement.setString(3, newEntity.getPasswordToken());
            int result = preparedStatement.executeUpdate();
            logger.traceExit("Saved {} instances", result);
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
    }

    @Override
    public void delete(Long id) {
    }

    @Override
    public void update(User updatedEntity) {
        logger.traceEntry("updating with task {} ", updatedEntity);
        Connection connection = jdbcUtils.getConnection();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "UPDATE users SET fullName=? WHERE id=?")) {
            preparedStatement.setString(1, updatedEntity.getFullName());
            preparedStatement.setLong(2, updatedEntity.getID());
            int result = preparedStatement.executeUpdate();
            logger.traceExit("Updated {} instances", result);
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
    }

    private User extract(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        String username = resultSet.getString("username");
        String fullName = resultSet.getString("fullName");
        String passwordToken = resultSet.getString("password");

        User user = new User(username, fullName);
        user.setID(id);
        user.setPasswordToken(passwordToken);
        return user;
    }
}
