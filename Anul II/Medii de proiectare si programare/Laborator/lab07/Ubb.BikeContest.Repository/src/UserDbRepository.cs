using System.Collections;
using System.Data;
using log4net;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Repository;

public class UserDbRepository : IUserRepository
{
    private static readonly ILog Log = LogManager.GetLogger("UserDbRepository");
    private readonly IDictionary<string, string?> _props;

    public UserDbRepository(IDictionary<string, string?> props)
    {
        Log.Info("Creating UserDbRepository ");
        _props = props;
    }

    public User FindById(long id)
    {
        Log.InfoFormat("Entering Get with value {0}", id);
        var connection = DbUtils.GetConnection(_props);

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "SELECT id,username,fullName,password FROM users WHERE id=@id";
            IDbDataParameter paramId = command.CreateParameter();
            paramId.ParameterName = "@id";
            paramId.Value = id;
            command.Parameters.Add(paramId);

            using (var dataReader = command.ExecuteReader())
            {
                if (dataReader.Read())
                {
                    User user = Extract(dataReader);
                    Log.InfoFormat("Exiting Get with value {0}", user);
                    return user;
                }
            }
        }
        Log.InfoFormat("Exiting Get with value {0}", null);
        return null;
    }

    public IEnumerable<User> FindAll()
    {
        Log.InfoFormat("Entering Read");
        var connection = DbUtils.GetConnection(_props);
        IList<User> users = new List<User>();

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "SELECT id,username,fullName,password FROM users";
            using (var dataReader = command.ExecuteReader())
            {
                while (dataReader.Read())
                {
                    User user = Extract(dataReader);
                    users.Add(user);
                }
            }
        }
        Log.InfoFormat("Exiting Read with value {0}", users);
        return users;
    }

    public void Save(User newEntity)
    {
        Log.InfoFormat("Entering Add with value {0}", newEntity);
        var connection = DbUtils.GetConnection(_props);

        using var command = connection.CreateCommand();
        command.CommandText = 
            "INSERT INTO users(username, fullName, password) " +
            "VALUES(@username, @fullName, @password);";
        var username = command.CreateParameter();
        username.ParameterName = "@username";
        username.Value = newEntity.Username;
        command.Parameters.Add(username);
            
        var fullName = command.CreateParameter();
        fullName.ParameterName = "@fullName";
        fullName.Value = newEntity.FullName;
        command.Parameters.Add(fullName);
            
        var password = command.CreateParameter();
        password.ParameterName = "@password";
        password.Value = newEntity.Password;
        command.Parameters.Add(password);

        var result = command.ExecuteNonQuery();
        Log.InfoFormat("Added {0} entities", result);
    }

    public void Delete(long id)
    {
        Log.InfoFormat("Entering Delete with value {0}", id);
        var connection = DbUtils.GetConnection(_props);
        using var command = connection.CreateCommand();
        command.CommandText = "DELETE FROM users WHERE id=@id";
        var paramId = command.CreateParameter();
        paramId.ParameterName = "@id";
        paramId.Value = id;
        command.Parameters.Add(paramId);
        var result = command.ExecuteNonQuery();
        Log.InfoFormat("Deleted {0} entities", result);
    }

    public void Update(User updatedEntity)
    {
        Log.InfoFormat("Entering Update with value {0}", updatedEntity);
        var connection = DbUtils.GetConnection(_props);

        using var command = connection.CreateCommand();
        command.CommandText = 
            "UPDATE users SET username=@username, fullName=@fullName, password=@password WHERE id=@id";
        var username = command.CreateParameter();
        username.ParameterName = "@username";
        username.Value = updatedEntity.Username;
        command.Parameters.Add(username);
            
        var fullName = command.CreateParameter();
        fullName.ParameterName = "@fullName";
        fullName.Value = updatedEntity.FullName;
        command.Parameters.Add(fullName);
            
        var password = command.CreateParameter();
        password.ParameterName = "@password";
        password.Value = updatedEntity.Password;
        command.Parameters.Add(password);

        var id = command.CreateParameter();
        id.ParameterName = "@id";
        id.Value = updatedEntity.Id;
        command.Parameters.Add(id);

        var result = command.ExecuteNonQuery();
        Log.InfoFormat("Updated {0} entities", result);
    }

    public User GetByUsername(string username)
    {
        Log.InfoFormat("Entering GetByUsername with value {0}", username);
        var connection = DbUtils.GetConnection(_props);

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "SELECT id,username,fullName,password FROM users WHERE username=@username";
            var paramUsername = command.CreateParameter();
            paramUsername.ParameterName = "@username";
            paramUsername.Value = username;
            command.Parameters.Add(paramUsername);

            using (var dataReader = command.ExecuteReader())
            {
                if (dataReader.Read())
                {
                    User user = Extract(dataReader);
                    Log.InfoFormat("Exiting GetByUsername with value {0}", user);
                    return user;
                }
            }
        }
        Log.InfoFormat("Exiting GetByUsername with value {0}", null);
        return null;
    }

    public User GetByUsernameAndPassword(string username, string password)
    {
        Log.InfoFormat("Entering GetByUsernameAndPassword with value {0}", username);
        var connection = DbUtils.GetConnection(_props);

        using (var command = connection.CreateCommand())
        {
            command.CommandText = "SELECT id,username,fullName,password FROM users WHERE username=@username " +
                                  "AND password=@password";
            var paramUsername = command.CreateParameter();
            paramUsername.ParameterName = "@username";
            paramUsername.Value = username;
            command.Parameters.Add(paramUsername);
            
            var paramPassword = command.CreateParameter();
            paramPassword.ParameterName = "@password";
            paramPassword.Value = password;
            command.Parameters.Add(paramPassword);

            using (var dataReader = command.ExecuteReader())
            {
                if (dataReader.Read())
                {
                    User user = Extract(dataReader);
                    Log.InfoFormat("Exiting GetByUsernameAndPassword with value {0}", user);
                    return user;
                }
            }
        }
        Log.InfoFormat("Exiting GetByUsernameAndPassword with value {0}", null);
        return null;
    }

    private User Extract(IDataReader dataReader)
    {
        var id = dataReader.GetInt64(0);
        var username = dataReader.GetString(1);
        var fullName = dataReader.GetString(2);
        var password = dataReader.GetString(3);

        var user = new User(username, fullName, password)
        {
            Id = id
        };
        return user;
    }
}