package com.ubb.repository;

import com.ubb.model.Participant;
import com.ubb.utils.JDBCUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.*;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Optional;
import java.util.Properties;

public class ParticipantDBRepository implements IParticipantRepository {
    private final JDBCUtils dbUtils;
    private static final Logger logger = LogManager.getLogger();

    public ParticipantDBRepository(final Properties properties) {
        logger.info("Initializing ParticipantDBRepository with properties: {} ", properties);
        dbUtils = new JDBCUtils(properties);
    }

    @Override
    public Collection<Participant> getParticipantsByTeam(Long teamID) {
        logger.traceEntry();
        Connection connection = dbUtils.getConnection();
        Collection<Participant> participants = new ArrayList<>();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT * FROM participants WHERE teamID=?")) {
            preparedStatement.setLong(1, teamID);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    Participant participant = extract(resultSet);
                    participants.add(participant);
                }
            }
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
        logger.traceExit(participants);
        return participants;
    }

    @Override
    public Optional<Participant> findById(Long id) {
        logger.traceEntry();
        Connection connection = dbUtils.getConnection();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT * FROM participants WHERE id=?")) {
            preparedStatement.setLong(1, id);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    Participant participant = extract(resultSet);
                    logger.traceExit(participant);
                    return Optional.of(participant);
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
    public Collection<Participant> findAll() {
        logger.traceEntry();
        Connection connection = dbUtils.getConnection();
        Collection<Participant> participants = new ArrayList<>();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT * FROM participants")) {
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    Participant participant = extract(resultSet);
                    participants.add(participant);
                }
            }
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
        logger.traceExit(participants);
        return participants;
    }

    @Override
    public void save(Participant newEntity) {
        logger.traceEntry("saving task {} ", newEntity);
        Connection connection = dbUtils.getConnection();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "INSERT INTO participants (firstname, lastname, engineCc, teamID) " +
                        "VALUES (?,?,?,?)")) {
            setParams(newEntity, preparedStatement);
            final int result = preparedStatement.executeUpdate();
            logger.trace("Saved {} instances", result);
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
    }

    @Override
    public void delete(Long id) {
        logger.traceEntry("deleting task of id={} ", id);
        Connection connection = dbUtils.getConnection();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "DELETE FROM participants WHERE id=?")) {
            preparedStatement.setLong(1, id);
            final int result = preparedStatement.executeUpdate();
            logger.trace("Deleted {} instances", result);
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
    }

    @Override
    public void update(Participant updatedEntity) {
        logger.traceEntry("updating with task {} ", updatedEntity);
        Connection connection = dbUtils.getConnection();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "UPDATE participants SET firstname=?, lastname=?, engineCc=?, teamID=? WHERE id=?")) {
            setParams(updatedEntity, preparedStatement);
            preparedStatement.setLong(5, updatedEntity.getID());
            final int result = preparedStatement.executeUpdate();
            logger.trace("Updated {} instances", result);
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
    }

    private void setParams(Participant updatedEntity, PreparedStatement preparedStatement) throws SQLException {
        preparedStatement.setString(1, updatedEntity.getFirstName());
        preparedStatement.setString(2, updatedEntity.getLastName());
        preparedStatement.setInt(3, updatedEntity.getEngineCapacity());
        if (updatedEntity.getTeamID().isPresent()) {
            preparedStatement.setLong(4, updatedEntity.getTeamID().get());
        } else {
            preparedStatement.setNull(4, Types.INTEGER);
        }
    }

    private Participant extract(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        String firstName = resultSet.getString("firstname");
        String lastName = resultSet.getString("lastname");
        Integer engineCapacity = resultSet.getInt("engineCc");
        Long teamID = resultSet.getLong("teamID");

        Participant participant = new Participant(firstName, lastName, engineCapacity);
        participant.setID(id);
        participant.setTeamID(teamID);
        return participant;
    }
}
