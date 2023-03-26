package com.ubb.repository;

import com.ubb.model.Race;
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

public class RaceDBRepository implements IRaceRepository {
    private final JDBCUtils jdbcUtils;
    private static final Logger logger = LogManager.getLogger();

    public RaceDBRepository(final Properties properties) {
        logger.info("Initializing RaceDBRepository with properties: {} ", properties);
        jdbcUtils = new JDBCUtils(properties);
    }

    @Override
    public Optional<Race> getRaceByName(String name) {
        logger.traceEntry("getRaceByName with task {} ", name);
        Connection connection = jdbcUtils.getConnection();
        Collection<Race> races = new ArrayList<>();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT * FROM races WHERE name=?")) {
            preparedStatement.setString(1, name);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    Optional<Race> race = Optional.of(extract(resultSet));
                    logger.traceExit(race.get());
                    return race;
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
    public Collection<Race> getRacesByEngineCapacity(Integer engineCapacity) {
        logger.traceEntry("getRacesByEngineCapacity with task {} ", engineCapacity);
        Connection connection = jdbcUtils.getConnection();
        Collection<Race> races = new ArrayList<>();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT * FROM races WHERE engineCc=?")) {
            preparedStatement.setInt(1, engineCapacity);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    Race race = extract(resultSet);
                    races.add(race);
                }
            }
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
        logger.traceExit(races);
        return races;
    }

    @Override
    public Optional<Race> findById(Long id) {
        logger.traceEntry();
        Connection connection = jdbcUtils.getConnection();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT * FROM races WHERE id=?")) {
            preparedStatement.setLong(1, id);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    Race race = extract(resultSet);
                    logger.traceExit(race);
                    return Optional.of(race);
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
    public Collection<Race> findAll() {
        logger.traceEntry();
        Connection connection = jdbcUtils.getConnection();
        Collection<Race> races = new ArrayList<>();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT * FROM races")) {
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    Race race = extract(resultSet);
                    races.add(race);
                }
            }
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
        logger.traceExit(races);
        return races;
    }

    @Override
    public void save(Race newEntity) {
        logger.traceEntry("saving task {} ", newEntity);
        Connection connection = jdbcUtils.getConnection();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "INSERT INTO races (name, engineCc) VALUES (?,?)")) {
            preparedStatement.setString(1, newEntity.getName());
            preparedStatement.setInt(2, newEntity.getEngineCapacity());
            final int result = preparedStatement.executeUpdate();
            logger.traceExit("Saved {} instances ", result);
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
    }

    @Override
    public void delete(Long id) {
        logger.traceEntry("deleting task of id={} ", id);
        Connection connection = jdbcUtils.getConnection();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "DELETE FROM races WHERE id=?")) {
            preparedStatement.setLong(1, id);
            final int result = preparedStatement.executeUpdate();
            logger.traceExit("Deleted {} instances", result);
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
    }

    @Override
    public void update(Race updatedEntity) {
        logger.traceEntry("updating with task {} ", updatedEntity);
        Connection connection = jdbcUtils.getConnection();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "UPDATE races SET name=?, engineCc=? where id=?")) {
            preparedStatement.setString(1, updatedEntity.getName());
            preparedStatement.setInt(2, updatedEntity.getEngineCapacity());
            preparedStatement.setLong(3, updatedEntity.getID());
            int result = preparedStatement.executeUpdate();
            logger.traceExit("Updated {} instances");
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
    }

    private Race extract(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        String name = resultSet.getString("name");
        Integer engineCapacity = resultSet.getInt("engineCc");

        Race race = new Race(name, engineCapacity);
        race.setID(id);
        return race;
    }
}
