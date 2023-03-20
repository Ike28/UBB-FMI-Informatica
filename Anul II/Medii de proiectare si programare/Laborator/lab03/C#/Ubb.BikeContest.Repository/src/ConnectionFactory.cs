using System.Data;
using System.Reflection;

namespace Ubb.BikeContest.Repository;

public abstract class ConnectionFactory
{
    protected ConnectionFactory()
    {
        
    }

    private static ConnectionFactory _connectionFactory;

    public static ConnectionFactory GetInstance()
    {
        if (_connectionFactory == null)
        {
            Assembly assembly = Assembly.GetExecutingAssembly();
            Type[] types = assembly.GetTypes();
            foreach (var type in types)
            {
                if (type.IsSubclassOf(typeof(ConnectionFactory)))
                {
                    _connectionFactory = (ConnectionFactory)Activator.CreateInstance(type);
                }
            }
        }

        return _connectionFactory;
    }

    public abstract IDbConnection CreateConnection(IDictionary<string, string> props);
}