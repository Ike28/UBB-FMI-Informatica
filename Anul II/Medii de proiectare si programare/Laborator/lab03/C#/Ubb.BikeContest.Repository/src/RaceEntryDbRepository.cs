using System.Collections;
using System.Data;
using log4net;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Repository;

public class RaceEntryDbRepository : IRaceEntryRepository
{
    private static readonly ILog Log = LogManager.GetLogger("RaceEntryDbRepository");
    private IDictionary<String, string> _props;
    private IRaceRepository _raceRepository;
    private IParticipantRepository _participantRepository;

    public RaceEntryDbRepository(IDictionary<String, string> props, 
        IRaceRepository raceRepository, IParticipantRepository participantRepository)
    {
        Log.Info("Creating RaceEntryDbRepository ");
        _props = props;
        _raceRepository = raceRepository;
        _participantRepository = participantRepository;
    }

    public RaceEntry Get(long id)
    {
        Log.InfoFormat("Entering Get with value {0}", id);
        IDbConnection connection = DBUtils.GetConnection(_props);

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "SELECT id,participantID,raceID FROM race_entries WHERE id=@id";
            IDbDataParameter paramId = command.CreateParameter();
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

    public IEnumerable Read()
    {
        Log.InfoFormat("Entering Read");
        IDbConnection connection = DBUtils.GetConnection(_props);
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

    public void Add(RaceEntry newEntity)
    {
        Log.InfoFormat("Entering Add with value {0}", newEntity);
        IDbConnection connection = DBUtils.GetConnection(_props);

        using (var command = connection.CreateCommand())
        {
            command.CommandText = 
                "INSERT INTO race_entries(participantID, raceID) " +
                "VALUES(@participantID, @raceID);";
            var participantID = command.CreateParameter();
            participantID.ParameterName = "@participantID";
            participantID.Value = newEntity.Participant.Id;
            command.Parameters.Add(participantID);

            var raceID = command.CreateParameter();
            raceID.ParameterName = "@raceID";
            raceID.Value = newEntity.Race.Id;
            command.Parameters.Add(raceID);

            var result = command.ExecuteNonQuery();
            Log.InfoFormat("Added {0} entities", result);
        }
    }

    public void Delete(long id)
    {
        Log.InfoFormat("Entering Delete with value {0}", id);
        IDbConnection connection = DBUtils.GetConnection(_props);
        using (var command = connection.CreateCommand())
        {
            command.CommandText = "DELETE FROM race_entries WHERE id=@id";
            var paramId = command.CreateParameter();
            paramId.ParameterName = "@id";
            paramId.Value = id;
            command.Parameters.Add(paramId);
            var result = command.ExecuteNonQuery();
            Log.InfoFormat("Deleted {0} entities", result);
        }
    }

    public void Update(RaceEntry updatedEntity)
    {
        throw new NotImplementedException();
    }

    public IEnumerable GetEntriesByRace(long raceId)
    {
        Log.InfoFormat("Entering GetEntriesByRace");
        IDbConnection connection = DBUtils.GetConnection(_props);
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
    
    private RaceEntry Extract(IDataReader dataReader)
    {
        long id = dataReader.GetInt64(0);
        long participantId = dataReader.GetInt64(1);
        long raceId = dataReader.GetInt64(2);

        Participant participant = _participantRepository.Get(participantId);
        Race race = _raceRepository.Get(raceId);
        RaceEntry raceEntry = new RaceEntry(participant, race);
        return raceEntry;
    }
}