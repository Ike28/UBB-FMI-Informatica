using System.Collections;
using System.Collections.ObjectModel;
using System.Data;
using Ubb.BikeContest.Model;
using log4net;

namespace Ubb.BikeContest.Repository;

public class ParticipantDBRepository : IParticipantRepository
{
    private static readonly ILog log = LogManager.GetLogger("ParticipantDBRepository");
    private IDictionary<String, string> props;

    public ParticipantDBRepository(IDictionary<String, string> props)
    {
        log.Info("Creating ParticipantDBRepository ");
        this.props = props;
    }
    
    public Participant Get(long id)
    {
        log.InfoFormat("Entering Get with value {0}", id);
        IDbConnection connection = DBUtils.GetConnection(props);

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "SELECT id,firstname,lastname,engineCc,teamID FROM participants WHERE id=@id";
            IDbDataParameter paramId = command.CreateParameter();
            paramId.ParameterName = "@id";
            paramId.Value = id;
            command.Parameters.Add(paramId);

            using (var dataReader = command.ExecuteReader())
            {
                if (dataReader.Read())
                {
                    Participant participant = Extract(dataReader);
                    log.InfoFormat("Exiting Get with value {0}", participant);
                    return participant;
                }
            }
        }
        log.InfoFormat("Exiting Get with value {0}", null);
        return null;
    }

    public IEnumerable Read()
    {
        log.InfoFormat("Entering Read");
        IDbConnection connection = DBUtils.GetConnection(props);
        IList<Participant> participants = new List<Participant>();

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "SELECT id,firstname,lastname,engineCc,teamID FROM participants";
            using (var dataReader = command.ExecuteReader())
            {
                while (dataReader.Read())
                {
                    Participant participant = Extract(dataReader);
                    participants.Add(participant);
                }
            }
        }
        log.InfoFormat("Exiting Read with value {0}", participants);
        return participants;
    }

    public void Add(Participant newEntity)
    {
        log.InfoFormat("Entering Add with value {0}", newEntity);
        IDbConnection connection = DBUtils.GetConnection(props);

        using (var command = connection.CreateCommand())
        {
            command.CommandText = 
                "INSERT INTO participants(firstname, lastname, engineCc,teamID) " +
                "VALUES(@firstname, @lastname, @engineCc, @teamID);";
            var firstname = command.CreateParameter();
            firstname.ParameterName = "@firstname";
            firstname.Value = newEntity.FirstName;
            command.Parameters.Add(firstname);

            var lastname = command.CreateParameter();
            lastname.ParameterName = "@lastname";
            lastname.Value = newEntity.LastName;
            command.Parameters.Add(lastname);

            var engineCapacity = command.CreateParameter();
            engineCapacity.ParameterName = "@engineCc";
            engineCapacity.Value = newEntity.EngineCapacity;
            command.Parameters.Add(engineCapacity);

            var teamId = command.CreateParameter();
            teamId.ParameterName = "@teamID";
            teamId.Value = newEntity.TeamId;
            command.Parameters.Add(teamId);

            var result = command.ExecuteNonQuery();
            log.InfoFormat("Added {0} entities", result);
        }
    }

    public void Delete(long id)
    {
        log.InfoFormat("Entering Delete with value {0}", id);
        IDbConnection connection = DBUtils.GetConnection(props);
        using (var command = connection.CreateCommand())
        {
            command.CommandText = "DELETE FROM participants WHERE id=@id";
            var paramId = command.CreateParameter();
            paramId.ParameterName = "@id";
            paramId.Value = id;
            command.Parameters.Add(paramId);
            var result = command.ExecuteNonQuery();
            log.InfoFormat("Deleted {0} entities", result);
        }
    }

    public void Update(Participant updatedEntity)
    {
        log.InfoFormat("Entering Update with value {0}", updatedEntity);
        IDbConnection connection = DBUtils.GetConnection(props);

        using (var command = connection.CreateCommand())
        {
            command.CommandText = 
                "UPDATE participants SET firstname=@firstname, lastname=@lastname, engineCc=@engineCc, teamID=@teamID " +
                "WHERE id=@id";
            var firstname = command.CreateParameter();
            firstname.ParameterName = "@firstname";
            firstname.Value = updatedEntity.FirstName;
            command.Parameters.Add(firstname);

            var lastname = command.CreateParameter();
            lastname.ParameterName = "@lastname";
            lastname.Value = updatedEntity.LastName;
            command.Parameters.Add(lastname);

            var engineCapacity = command.CreateParameter();
            engineCapacity.ParameterName = "@engineCc";
            engineCapacity.Value = updatedEntity.EngineCapacity;
            command.Parameters.Add(engineCapacity);

            var teamId = command.CreateParameter();
            teamId.ParameterName = "@teamID";
            teamId.Value = updatedEntity.TeamId;
            command.Parameters.Add(teamId);

            var id = command.CreateParameter();
            id.ParameterName = "@id";
            id.Value = updatedEntity.Id;
            command.Parameters.Add(id);

            var result = command.ExecuteNonQuery();
            log.InfoFormat("Updated {0} entities", result);
        }
    }

    public IEnumerable GetParticipantsByTeam(long teamId)
    {
        log.InfoFormat("Entering GetParticipantsByTeam with value {0}", teamId);
        IDbConnection connection = DBUtils.GetConnection(props);
        IList<Participant> participants = new List<Participant>();

        using (var command = connection.CreateCommand())
        {
            command.CommandText = 
                "SELECT id,firstname,lastname,engineCc,teamID FROM participants WHERE teamID=@teamID";
            var paramTeamId = command.CreateParameter();
            paramTeamId.ParameterName = "@teamID";
            paramTeamId.Value = teamId;
            command.Parameters.Add(paramTeamId);
            using (var dataReader = command.ExecuteReader())
            {
                while (dataReader.Read())
                {
                    Participant participant = Extract(dataReader);
                    participants.Add(participant);
                }
            }
        }
        log.InfoFormat("Exiting GetParticipantsByTeam with value {0}", participants);
        return participants;
    }

    private Participant Extract(IDataReader dataReader)
    {
        long id = dataReader.GetInt64(0);
        String firstName = dataReader.GetString(1);
        String lastName = dataReader.GetString(2);
        int engineCapacity = dataReader.GetInt32(3);
        long? teamID = null;
        if (!dataReader.IsDBNull(4))
        {
            teamID = dataReader.GetInt64(4);
        }

        Participant participant = new Participant(firstName, lastName, engineCapacity);
        participant.Id = id;
        participant.TeamId = teamID; 
        return participant;
    }
}