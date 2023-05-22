package com.ubb.repository.hibernate;

import com.ubb.model.Participant;
import com.ubb.repository.IParticipantRepository;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.query.Query;

import java.util.Collection;
import java.util.Optional;

public class ParticipantORMRepository implements IParticipantRepository {
    private final SessionFactory sessionFactory;
    private static final Logger logger = LogManager.getLogger();

    public ParticipantORMRepository(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    @Override
    public Collection<Participant> getParticipantsByTeam(Long teamID) {
        try (Session session = sessionFactory.openSession()) {
            Query<Participant> query = session.createQuery(
                    "FROM Participant WHERE teamID = :teamID", Participant.class)
                    .setParameter("teamID", teamID);
            return query.list();
        } catch (Exception exception) {
            logger.error(exception);
            return null;
        }
    }

    @Override
    public Optional<Participant> getParticipantByData(Participant participant) {
        try (Session session = sessionFactory.openSession()) {
            Query<Participant> query = session.createQuery(
                            "FROM Participant WHERE firstName = :firstname " +
                                    "AND lastName = :lastname AND engineCapacity = :engineCC AND teamID = :teamID",
                                    Participant.class)
                    .setParameter("firstname", participant.getFirstName())
                    .setParameter("lastname", participant.getLastName())
                    .setParameter("engineCC", participant.getEngineCapacity())
                    .setParameter("teamID", participant.getTeamID());
            return query.uniqueResultOptional();
        } catch (Exception exception) {
            logger.error(exception);
            return Optional.empty();
        }
    }

    @Override
    public Optional<Participant> findById(Long id) {
        try (Session session = sessionFactory.openSession()) {
            return Optional.of(session.get(Participant.class, id));
        } catch (Exception exception) {
            logger.error(exception);
            return Optional.empty();
        }
    }

    @Override
    public Collection<Participant> findAll() {
        try (Session session = sessionFactory.openSession()) {
            Query<Participant> query = session.createQuery("FROM Participant", Participant.class);
            return query.list();
        } catch (Exception exception) {
            logger.error(exception);
            return null;
        }
    }

    @Override
    public void save(Participant newEntity) {
        Transaction transaction = null;
        try (Session session = sessionFactory.openSession()) {
            transaction = session.beginTransaction();
            session.persist(newEntity);
            transaction.commit();
        } catch (Exception exception) {
            if (transaction != null) {
                transaction.rollback();
            }
            logger.error(exception);
        }
    }

    @Override
    public void delete(Long aLong) {
        Transaction transaction = null;
        try (Session session = sessionFactory.openSession()) {
            transaction = session.beginTransaction();
            Optional<Participant> existing = findById(aLong);
            existing.ifPresent(session::remove);
            transaction.commit();
        } catch (Exception exception) {
            if (transaction != null) {
                transaction.rollback();
            }
            logger.error(exception);
        }
    }

    @Override
    public void update(Participant updatedEntity) {
        Transaction transaction = null;
        try (Session session = sessionFactory.openSession()) {
            transaction = session.beginTransaction();
            session.merge(updatedEntity);
            transaction.commit();
        } catch (Exception exception) {
            if (transaction != null) {
                transaction.rollback();
            }
            logger.error(exception);
        }
    }
}
