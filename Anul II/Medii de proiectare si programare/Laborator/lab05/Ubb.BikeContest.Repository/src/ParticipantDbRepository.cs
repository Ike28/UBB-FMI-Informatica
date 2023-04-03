using System.Collections;
using System.Data;
using Ubb.BikeContest.Model;
using log4net;

namespace Ubb.BikeContest.Repository;

public class ParticipantDbRepository : IParticipantRepository
{
    private static readonly ILog Log = LogManager.GetLogger("ParticipantDbRepository");
    private readonly IDictionary<string, string?> _props;

    public ParticipantDbRepository(IDictionary<string, string?> props)
    {
        Log.Info("Creating ParticipantDbRepository ");
        _props = props;
    }
    
    public Participant FindById(long id)
    {
        Log.InfoFormat("Entering Get with value {0}", id);
        IDbConnection connection = DbUtils.GetConnection(_props);

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "SELECT id,firstname,lastname,engineCc,teamID FROM participants WHERE id=@id";
            var paramId = command.CreateParameter();
            paramId.ParameterName = "@id";
            paramId.Value = id;
            command.Parameters.Add(paramId);

            using (var dataReader = command.ExecuteReader())
            {
                if (dataReader.Read())
                {
                    Participant participant = Extract(dataReader);
                    Log.InfoFormat("Exiting Get with value {0}", participant);
                    return participant;
                }
            }
        }
        Log.InfoFormat("Exiting Get with value {0}", null);
        return null;
    }

    public IEnumerable<Participant> FindAll()
    {
        Log.InfoFormat("Entering Read");
        IDbConnection connection = DbUtils.GetConnection(_props);
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
        Log.InfoFormat("Exiting Read with value {0}", participants);
        return participants;
    }

    public void Save(Participant newEntity)
    {
        Log.InfoFormat("Entering Add with value {0}", newEntity);
        IDbConnection connection = DbUtils.GetConnection(_props);

        using var command = connection.CreateCommand();
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
        Log.InfoFormat("Added {0} entities", result);
    }

    public void Delete(long id)
    {
        Log.InfoFormat("Entering Delete with value {0}", id);
        IDbConnection connection = DbUtils.GetConnection(_props);
        using var command = connection.CreateCommand();
        command.CommandText = "DELETE FROM participants WHERE id=@id";
        var paramId = command.CreateParameter();
        paramId.ParameterName = "@id";
        paramId.Value = id;
        command.Parameters.Add(paramId);
        var result = command.ExecuteNonQuery();
        Log.InfoFormat("Deleted {0} entities", result);
    }

    public void Update(Participant updatedEntity)
    {
        Log.InfoFormat("Entering Update with value {0}", updatedEntity);
        IDbConnection connection = DbUtils.GetConnection(_props);

        using var command = connection.CreateCommand();
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
        Log.InfoFormat("Updated {0} entities", result);
    }

    public IEnumerable<Participant> GetParticipantsByTeam(long teamId)
    {
        Log.InfoFormat("Entering GetParticipantsByTeam with value {0}", teamId);
        var connection = DbUtils.GetConnection(_props);
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
        Log.InfoFormat("Exiting GetParticipantsByTeam with value {0}", participants);
        return participants;
    }

    public Participant GetParticipantByData(Participant participant)
    {
        Log.InfoFormat("Entering GetParticipantByData with value {0}", participant);
        IDbConnection connection = DbUtils.GetConnection(_props);

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "SELECT id,firstname,lastname,engineCc,teamID FROM participants WHERE " +
                                  "firstname=@firstname AND lastname=@lastname AND engineCc=@engineCc " +
                                  "AND teamID=@teamID";
            var firstname = command.CreateParameter();
            firstname.ParameterName = "@firstname";
            firstname.Value = participant.FirstName;
            command.Parameters.Add(firstname);
                
            var lastname = command.CreateParameter();
            lastname.ParameterName = "@lastname";
            lastname.Value = participant.LastName;
            command.Parameters.Add(lastname);
                
            var engineCc = command.CreateParameter();
            engineCc.ParameterName = "@engineCc";
            engineCc.Value = participant.EngineCapacity;
            command.Parameters.Add(engineCc);
                
            var teamId = command.CreateParameter();
            teamId.ParameterName = "@teamID";
            teamId.Value = participant.TeamId;
            command.Parameters.Add(teamId);

            using (var dataReader = command.ExecuteReader())
            {
                if (dataReader.Read())
                {
                    Participant extracted = Extract(dataReader);
                    Log.InfoFormat("Exiting GetParticipantByData with value {0}", extracted);
                    return extracted;
                }
            }
        }
        Log.InfoFormat("Exiting GetParticipantByData with value {0}", null);
        return null;
    }

    private static Participant Extract(IDataReader dataReader)
    {
        var id = dataReader.GetInt64(0);
        var firstName = dataReader.GetString(1);
        var lastName = dataReader.GetString(2);
        var engineCapacity = dataReader.GetInt32(3);
        long? teamId = null;
        if (!dataReader.IsDBNull(4))
        {
            teamId = dataReader.GetInt64(4);
        }

        var participant = new Participant(firstName, lastName, engineCapacity)
        {
            Id = id,
            TeamId = teamId
        };
        return participant;
    }
}