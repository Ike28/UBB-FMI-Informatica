using System.Data;

namespace Ubb.BikeContest.Repository;

public static class DbUtils
{
    private static IDbConnection? _connection = null;

    public static IDbConnection GetConnection(IDictionary<string, string?> props)
    {
        if (_connection != null && _connection.State != System.Data.ConnectionState.Closed) return _connection;
        _connection = GetNewConnection(props);
        _connection.Open();

        return _connection;
    }

    private static IDbConnection GetNewConnection(IDictionary<string, string?> props)
    {
        return ConnectionFactory.GetInstance().CreateConnection(props);
    }
}