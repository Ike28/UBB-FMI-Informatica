using System.Data;
using Mono.Data.Sqlite;

namespace Ubb.BikeContest.Repository;

public class SqliteConnectionFactory : ConnectionFactory
{
    public override IDbConnection CreateConnection(IDictionary<string, string> props)
    {
        String connectionString = props["ConnectionString"];
        Console.WriteLine("SQLite ---Opening connection at ... {0}", connectionString);
        return new SqliteConnection(connectionString);
    }
}