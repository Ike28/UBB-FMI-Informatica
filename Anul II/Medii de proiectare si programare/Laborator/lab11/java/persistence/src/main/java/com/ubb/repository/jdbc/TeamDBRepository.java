package com.ubb.repository.jdbc;

import com.ubb.model.Team;
import com.ubb.repository.ITeamRepository;
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

public class TeamDBRepository implements ITeamRepository {
    private final JDBCUtils jdbcUtils;
    private static final Logger logger = LogManager.getLogger();

    public TeamDBRepository(Properties properties) {
        logger.info("Initializing TeamDBRepository with properties: {} ", properties);
        jdbcUtils = new JDBCUtils(properties);
    }

    @Override
    public Optional<Team> getTeamByName(String teamName) {
        logger.traceEntry("getTeamByName with task {} ", teamName);
        Connection connection = jdbcUtils.getConnection();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT * FROM teams WHERE name=?")) {
            preparedStatement.setString(1, teamName);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    Team team = extract(resultSet);
                    logger.traceExit(team);
                    return Optional.of(team);
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
    public Optional<Team> findById(Long id) {
        logger.traceEntry();
        Connection connection = jdbcUtils.getConnection();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT * FROM teams WHERE id=?")) {
            preparedStatement.setLong(1, id);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    Team team = extract(resultSet);
                    logger.traceExit(team);
                    return Optional.of(team);
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
    public Collection<Team> findAll() {
        logger.traceEntry();
        Connection connection = jdbcUtils.getConnection();
        Collection<Team> teams = new ArrayList<>();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT * FROM teams")) {
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    Team team = extract(resultSet);
                    teams.add(team);
                }
            }
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
        logger.traceExit(teams);
        return teams;
    }

    @Override
    public void save(Team newEntity) {
        logger.traceEntry("saving task {} ", newEntity);
        Connection connection = jdbcUtils.getConnection();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "INSERT INTO teams (name) VALUES (?)")) {
            preparedStatement.setString(1, newEntity.getName());
            int result = preparedStatement.executeUpdate();
            logger.traceExit("Saved {} instances");
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
                "DELETE FROM teams WHERE id=?")) {
            preparedStatement.setLong(1, id);
            int result = preparedStatement.executeUpdate();
            logger.traceExit("Deleted {} instances", result);
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
    }

    @Override
    public void update(Team updatedEntity) {
    }

    private Team extract(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        String name = resultSet.getString("name");

        Team team = new Team(name);
        team.setId(id);
        return team;
    }
}
