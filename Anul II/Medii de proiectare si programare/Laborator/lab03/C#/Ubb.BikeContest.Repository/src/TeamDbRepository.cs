using System.Collections;
using System.Data;
using log4net;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Repository;

public class TeamDbRepository : ITeamRepository
{
    private static readonly ILog Log = LogManager.GetLogger("TeamDbRepository");
    private IDictionary<String, string> _props;

    public TeamDbRepository(IDictionary<String, string> props)
    {
        Log.Info("Creating TeamDbRepository ");
        _props = props;
    }

    public Team Get(long id)
    {
        Log.InfoFormat("Entering Get with value {0}", id);
        IDbConnection connection = DBUtils.GetConnection(_props);

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "SELECT id,name FROM teams WHERE id=@id";
            IDbDataParameter paramId = command.CreateParameter();
            paramId.ParameterName = "@id";
            paramId.Value = id;
            command.Parameters.Add(paramId);

            using (var dataReader = command.ExecuteReader())
            {
                if (dataReader.Read())
                {
                    Team team = Extract(dataReader);
                    Log.InfoFormat("Exiting Get with value {0}", team);
                    return team;
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
        IList<Team> teams = new List<Team>();

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "SELECT id,name FROM teams";
            using (var dataReader = command.ExecuteReader())
            {
                while (dataReader.Read())
                {
                    Team team = Extract(dataReader);
                    teams.Add(team);
                }
            }
        }
        Log.InfoFormat("Exiting Read with value {0}", teams);
        return teams;
    }

    public void Add(Team newEntity)
    {
        Log.InfoFormat("Entering Add with value {0}", newEntity);
        IDbConnection connection = DBUtils.GetConnection(_props);

        using (var command = connection.CreateCommand())
        {
            command.CommandText = 
                "INSERT INTO teams(name) VALUES(@name);";
            var name = command.CreateParameter();
            name.ParameterName = "@name";
            name.Value = newEntity.Name;
            command.Parameters.Add(name);

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
            command.CommandText = "DELETE FROM teams WHERE id=@id";
            var paramId = command.CreateParameter();
            paramId.ParameterName = "@id";
            paramId.Value = id;
            command.Parameters.Add(paramId);
            var result = command.ExecuteNonQuery();
            Log.InfoFormat("Deleted {0} entities", result);
        }
    }

    public void Update(Team updatedEntity)
    {
        throw new NotImplementedException();
    }

    public Team GetTeamByName(string teamName)
    {
        Log.InfoFormat("Entering GetTeamByName with value {0}", teamName);
        IDbConnection connection = DBUtils.GetConnection(_props);

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "SELECT id,name FROM teams WHERE name=@name";
            var name = command.CreateParameter();
            name.ParameterName = "@id";
            name.Value = teamName;
            command.Parameters.Add(name);

            using (var dataReader = command.ExecuteReader())
            {
                if (dataReader.Read())
                {
                    Team team = Extract(dataReader);
                    Log.InfoFormat("Exiting GetTeamByName with value {0}", team);
                    return team;
                }
            }
        }
        Log.InfoFormat("Exiting GetTeamByName with value {0}", null);
        return null;
    }
    
    private Team Extract(IDataReader dataReader)
    {
        long id = dataReader.GetInt64(0);
        String name = dataReader.GetString(1);

        Team team = new Team(name);
        team.Id = id;
        return team;
    }
}