package com.ubb.repository.jdbc;

import com.ubb.model.Participant;
import com.ubb.model.Race;
import com.ubb.model.RaceEntry;
import com.ubb.repository.IParticipantRepository;
import com.ubb.repository.IRaceEntryRepository;
import com.ubb.repository.IRaceRepository;
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

public class RaceEntryDBRepository implements IRaceEntryRepository {
    private final JDBCUtils jdbcUtils;
    private final IRaceRepository raceRepository;
    private final IParticipantRepository participantRepository;
    private static final Logger logger = LogManager.getLogger();

    public RaceEntryDBRepository(
            final Properties properties, final IRaceRepository raceRepository,
            final IParticipantRepository participantRepository) {
        logger.info("Initializing RaceEntryDBRepository with properties: {} ", properties);
        jdbcUtils = new JDBCUtils(properties);
        this.raceRepository = raceRepository;
        this.participantRepository = participantRepository;
    }
    @Override
    public Collection<RaceEntry> getEntriesByRace(Long raceID) {
        logger.traceEntry("getEntriesByRace with task of id={} ", raceID);
        Connection connection = jdbcUtils.getConnection();
        Collection<RaceEntry> raceEntries = new ArrayList<>();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT * FROM race_entries WHERE raceID=?")) {
            preparedStatement.setLong(1, raceID);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    RaceEntry raceEntry = extract(resultSet);
                    raceEntries.add(raceEntry);
                }
            }
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
        logger.traceExit(raceEntries);
        return raceEntries;
    }

    @Override
    public void deleteByIds(Long participantID, Long raceID) {
        logger.traceEntry("deleting task of participantID={}, raceID={} ", participantID, raceID);
        Connection connection = jdbcUtils.getConnection();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "DELETE FROM race_entries WHERE participantID=? AND raceID=?")) {
            preparedStatement.setLong(1, participantID);
            preparedStatement.setLong(2, raceID);
            int result = preparedStatement.executeUpdate();
            logger.traceExit("Deleted {} instances", result);
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
    }

    @Override
    public Collection<Race> getRacesWhereNotRegisteredAndEngineCapacity(Long participantID, Integer engineCc) {
        logger.traceEntry("getRacesWhereNotRegistered with tasks {}, {} ", participantID, engineCc);
        Connection connection = jdbcUtils.getConnection();
        Collection<Race> raceEntries = new ArrayList<>();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT * FROM races WHERE id NOT IN " +
                        "(SELECT raceID from race_entries WHERE participantID=?)" +
                        " AND engineCc=?")) {
            preparedStatement.setLong(1, participantID);
            preparedStatement.setInt(2, engineCc);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    Race race = extractRace(resultSet);
                    raceEntries.add(race);
                }
            }
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
        logger.traceExit(raceEntries);
        return raceEntries;
    }

    @Override
    public Optional<RaceEntry> findById(Long id) {
        logger.traceEntry();
        Connection connection = jdbcUtils.getConnection();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "select * from race_entries where id=?")) {
            preparedStatement.setLong(1, id);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    RaceEntry raceEntry = extract(resultSet);
                    logger.traceExit(raceEntry);
                    return Optional.of(raceEntry);
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
    public Collection<RaceEntry> findAll() {
        logger.traceEntry();
        Connection connection = jdbcUtils.getConnection();
        Collection<RaceEntry> raceEntries = new ArrayList<>();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "SELECT * FROM race_entries")) {
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    RaceEntry raceEntry = extract(resultSet);
                    raceEntries.add(raceEntry);
                }
            }
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
        logger.traceExit(raceEntries);
        return raceEntries;
    }

    @Override
    public void save(RaceEntry newEntity) {
        logger.traceEntry("updating with task {} ", newEntity);
        Connection connection = jdbcUtils.getConnection();
        try (PreparedStatement preparedStatement = connection.prepareStatement(
                "INSERT INTO race_entries (participantID, raceID) values (?,?)")) {
            preparedStatement.setLong(1, newEntity.getParticipant().getId());
            preparedStatement.setLong(2, newEntity.getRace().getId());
            int result = preparedStatement.executeUpdate();
            logger.traceExit("Updated {} instances", result);
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
                "DELETE FROM race_entries where id=?")) {
            preparedStatement.setLong(1, id);
            int result = preparedStatement.executeUpdate();
            logger.traceExit("Deleted {} instances", result);
        } catch (SQLException sqlException) {
            logger.error(sqlException);
            System.err.println("DB Error : " + sqlException);
        }
    }

    @Override
    public void update(RaceEntry updatedEntity) {
    }

    private RaceEntry extract(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        Long participantID = resultSet.getLong("participantID");
        Long raceID = resultSet.getLong("raceID");

        final Optional<Race> race = raceRepository.findById(raceID);
        final Optional<Participant> participant = participantRepository.findById(participantID);
        if (participant.isPresent() && race.isPresent()) {
            RaceEntry raceEntry = new RaceEntry(participant.get(), race.get());
            raceEntry.setId(id);
            return raceEntry;
        } else {
            throw new SQLException("Database error: Unable to reference participant and/or race for Race Entry");
        }
    }

    private Race extractRace(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        String name = resultSet.getString("name");
        Integer engineCapacity = resultSet.getInt("engineCc");

        Race race = new Race(name, engineCapacity);
        race.setId(id);
        return race;
    }
}
