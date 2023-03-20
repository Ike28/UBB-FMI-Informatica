using System.Collections;
using System.Data;
using log4net;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Repository;

public class RaceDbRepository : IRaceRepository
{
    private static readonly ILog Log = LogManager.GetLogger("RaceDbRepository");
    private readonly IDictionary<string, string?> _props;

    public RaceDbRepository(IDictionary<string, string?> props)
    {
        Log.Info("Creating RaceDbRepository ");
        _props = props;
    }

    public Race FindById(long id)
    {
        Log.InfoFormat("Entering Get with value {0}", id);
        var connection = DbUtils.GetConnection(_props);

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "SELECT id,name,engineCc FROM races WHERE id=@id";
            var paramId = command.CreateParameter();
            paramId.ParameterName = "@id";
            paramId.Value = id;
            command.Parameters.Add(paramId);

            using (var dataReader = command.ExecuteReader())
            {
                if (dataReader.Read())
                {
                    Race race = Extract(dataReader);
                    Log.InfoFormat("Exiting Get with value {0}", race);
                    return race;
                }
            }
        }
        Log.InfoFormat("Exiting Get with value {0}", null);
        return null;
    }

    public IEnumerable FindAll()
    {
        Log.InfoFormat("Entering Read");
        var connection = DbUtils.GetConnection(_props);
        IList<Race> races = new List<Race>();

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "SELECT id,name,engineCc FROM races";
            using (var dataReader = command.ExecuteReader())
            {
                while (dataReader.Read())
                {
                    Race race = Extract(dataReader);
                    races.Add(race);
                }
            }
        }
        Log.InfoFormat("Exiting Read with value {0}", races);
        return races;
    }

    public void Save(Race newEntity)
    {
        Log.InfoFormat("Entering Add with value {0}", newEntity);
        var connection = DbUtils.GetConnection(_props);

        using var command = connection.CreateCommand();
        command.CommandText = 
            "INSERT INTO races(name, engineCc) " +
            "VALUES(@name, @engineCc);";
        var name = command.CreateParameter();
        name.ParameterName = "@name";
        name.Value = newEntity.Name;
        command.Parameters.Add(name);

        var engineCapacity = command.CreateParameter();
        engineCapacity.ParameterName = "@engineCc";
        engineCapacity.Value = newEntity.EngineCapacity;
        command.Parameters.Add(engineCapacity);

        var result = command.ExecuteNonQuery();
        Log.InfoFormat("Added {0} entities", result);
    }

    public void Delete(long id)
    {
        Log.InfoFormat("Entering Delete with value {0}", id);
        IDbConnection connection = DbUtils.GetConnection(_props);
        using var command = connection.CreateCommand();
        command.CommandText = "DELETE FROM races WHERE id=@id";
        var paramId = command.CreateParameter();
        paramId.ParameterName = "@id";
        paramId.Value = id;
        command.Parameters.Add(paramId);
        var result = command.ExecuteNonQuery();
        Log.InfoFormat("Deleted {0} entities", result);
    }

    public void Update(Race updatedEntity)
    {
        Log.InfoFormat("Entering Update with value {0}", updatedEntity);
        IDbConnection connection = DbUtils.GetConnection(_props);

        using var command = connection.CreateCommand();
        command.CommandText = 
            "UPDATE races SET name=@name, engineCc=@engineCc WHERE id=@id";
        var name = command.CreateParameter();
        name.ParameterName = "@name";
        name.Value = updatedEntity.Name;
        command.Parameters.Add(name);

        var engineCapacity = command.CreateParameter();
        engineCapacity.ParameterName = "@engineCc";
        engineCapacity.Value = updatedEntity.EngineCapacity;
        command.Parameters.Add(engineCapacity);

        var id = command.CreateParameter();
        id.ParameterName = "@id";
        id.Value = updatedEntity.Id;
        command.Parameters.Add(id);

        var result = command.ExecuteNonQuery();
        Log.InfoFormat("Updated {0} entities", result);
    }

    public Race GetRaceByName(string name)
    {
        Log.InfoFormat("Entering GetRaceByName with value {0}", name);
        IDbConnection connection = DbUtils.GetConnection(_props);

        using var command = connection.CreateCommand();
        command.CommandText = "SELECT id,name,engineCc FROM races WHERE name=@name";
        var paramName = command.CreateParameter();
        paramName.ParameterName = "@name";
        paramName.Value = name;
        command.Parameters.Add(paramName);

        using (var dataReader = command.ExecuteReader())
        {
            if (dataReader.Read())
            {
                Race race = Extract(dataReader);
                Log.InfoFormat("Exiting GetRaceByName with value {0}", race);
                return race;
            }
        }

        Log.InfoFormat("Exiting GetRaceByName with value {0}", null);
        return null;
    }

    private Race Extract(IDataReader dataReader)
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