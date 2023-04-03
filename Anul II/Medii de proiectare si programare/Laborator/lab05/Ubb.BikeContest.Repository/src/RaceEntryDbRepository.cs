using System.Collections;
using System.Data;
using log4net;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Repository;

public class RaceEntryDbRepository : IRaceEntryRepository
{
    private static readonly ILog Log = LogManager.GetLogger("RaceEntryDbRepository");
    private readonly IDictionary<string, string?> _props;
    private readonly IRaceRepository _raceRepository;
    private readonly IParticipantRepository _participantRepository;

    public RaceEntryDbRepository(IDictionary<string, string?> props, 
        IRaceRepository raceRepository, IParticipantRepository participantRepository)
    {
        Log.Info("Creating RaceEntryDbRepository ");
        _props = props;
        _raceRepository = raceRepository;
        _participantRepository = participantRepository;
    }

    public RaceEntry FindById(long id)
    {
        Log.InfoFormat("Entering Get with value {0}", id);
        var connection = DbUtils.GetConnection(_props);

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "SELECT id,participantID,raceID FROM race_entries WHERE id=@id";
            var paramId = command.CreateParameter();
            paramId.ParameterName = "@id";
            paramId.Value = id;
            command.Parameters.Add(paramId);

            using (var dataReader = command.ExecuteReader())
            {
                if (dataReader.Read())
                {
                    RaceEntry raceEntry = Extract(dataReader);
                    Log.InfoFormat("Exiting Get with value {0}", raceEntry);
                    return raceEntry;
                }
            }
        }
        Log.InfoFormat("Exiting Get with value {0}", null);
        return null;
    }

    public IEnumerable<RaceEntry> FindAll()
    {
        Log.InfoFormat("Entering Read");
        var connection = DbUtils.GetConnection(_props);
        IList<RaceEntry> raceEntries = new List<RaceEntry>();

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "SELECT id,participantID,raceID FROM race_entries";
            using (var dataReader = command.ExecuteReader())
            {
                while (dataReader.Read())
                {
                    RaceEntry raceEntry = Extract(dataReader);
                    raceEntries.Add(raceEntry);
                }
            }
        }
        Log.InfoFormat("Exiting Read with value {0}", raceEntries);
        return raceEntries;
    }

    public void Save(RaceEntry newEntity)
    {
        Log.InfoFormat("Entering Add with value {0}", newEntity);
        var connection = DbUtils.GetConnection(_props);

        using var command = connection.CreateCommand();
        command.CommandText = 
            "INSERT INTO race_entries(participantID, raceID) " +
            "VALUES(@participantID, @raceID);";
        var participantId = command.CreateParameter();
        participantId.ParameterName = "@participantID";
        participantId.Value = newEntity.Participant.Id;
        command.Parameters.Add(participantId);

        var raceId = command.CreateParameter();
        raceId.ParameterName = "@raceID";
        raceId.Value = newEntity.Race.Id;
        command.Parameters.Add(raceId);

        var result = command.ExecuteNonQuery();
        Log.InfoFormat("Added {0} entities", result);
    }

    public void Delete(long id)
    {
        Log.InfoFormat("Entering Delete with value {0}", id);
        var connection = DbUtils.GetConnection(_props);
        using var command = connection.CreateCommand();
        command.CommandText = "DELETE FROM race_entries WHERE id=@id";
        var paramId = command.CreateParameter();
        paramId.ParameterName = "@id";
        paramId.Value = id;
        command.Parameters.Add(paramId);
        var result = command.ExecuteNonQuery();
        Log.InfoFormat("Deleted {0} entities", result);
    }

    public void Update(RaceEntry updatedEntity)
    {
        throw new NotImplementedException();
    }

    public IEnumerable<RaceEntry> GetEntriesByRace(long raceId)
    {
        Log.InfoFormat("Entering GetEntriesByRace");
        var connection = DbUtils.GetConnection(_props);
        IList<RaceEntry> raceEntries = new List<RaceEntry>();

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "SELECT id,participantID,raceID FROM race_entries WHERE raceID=@raceID";
            var paramRaceId = command.CreateParameter();
            paramRaceId.ParameterName = "@raceID";
            paramRaceId.Value = raceId;
            command.Parameters.Add(paramRaceId);
            
            using (var dataReader = command.ExecuteReader())
            {
                while (dataReader.Read())
                {
                    RaceEntry raceEntry = Extract(dataReader);
                    raceEntries.Add(raceEntry);
                }
            }
        }
        Log.InfoFormat("Exiting GetEntriesByRace with value {0}", raceEntries);
        return raceEntries;
    }

    public IEnumerable<Race> GetRacesWhereNotRegisteredAndEngineCapacity(long participantId, int engineCapacity)
    {
        Log.InfoFormat("Entering GetRacesWhereNotRegisteredAndEngineCapacity with {0}, {1}",
            participantId, engineCapacity);
        var connection = DbUtils.GetConnection(_props);
        IList<Race> result = new List<Race>();

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "SELECT * FROM races WHERE id NOT IN " +
                                  "(SELECT raceID from race_entries WHERE participantID=@participantId)" +
                                  " AND engineCc=@engineCc";
            var paramParticipantId = command.CreateParameter();
            paramParticipantId.ParameterName = "@participantId";
            paramParticipantId.Value = participantId;
            command.Parameters.Add(paramParticipantId);
            
            var paramEngine = command.CreateParameter();
            paramEngine.ParameterName = "@engineCc";
            paramEngine.Value = engineCapacity;
            command.Parameters.Add(paramEngine);
            
            using (var dataReader = command.ExecuteReader())
            {
                while (dataReader.Read())
                {
                    Race race = ExtractRace(dataReader);
                    result.Add(race);
                }
            }
        }
        Log.InfoFormat("Exiting GetRacesWhereNotRegisteredAndEngineCapacity with value {0}", result);
        return result;
    }

    private RaceEntry Extract(IDataReader dataReader)
    {
        var id = dataReader.GetInt64(0);
        var participantId = dataReader.GetInt64(1);
        var raceId = dataReader.GetInt64(2);

        var participant = _participantRepository.FindById(participantId);
        var race = _raceRepository.FindById(raceId);
        var raceEntry = new RaceEntry(participant, race);
        return raceEntry;
    }
    
    private Race ExtractRace(IDataReader dataReader)
    {
        var id = dataReader.GetInt64(0);
        var name = dataReader.GetString(1);
        var engineCapacity = dataReader.GetInt32(2);

        var race = new Race(name, engineCapacity)
        {
            Id = id
        };
        return race;
    }
}