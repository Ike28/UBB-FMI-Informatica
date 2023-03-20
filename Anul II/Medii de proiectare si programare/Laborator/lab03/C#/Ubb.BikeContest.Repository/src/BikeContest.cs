using log4net.Config;
using System.Configuration;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Repository;

public static class BikeContest
{
    public static void Main(string[] args)
    {
        XmlConfigurator.Configure(new FileInfo("app.config"));
        Console.WriteLine("Configuration Settings for DB {0}",GetConnectionStringByName("bikeContestDB"));
        IDictionary<string, string?> props = new SortedList<string, string?>();
        props.Add("ConnectionString", GetConnectionStringByName("bikeContestDB"));

        var participantDbRepository = new ParticipantDbRepository(props);
        participantDbRepository.Save(new Participant("Mihai", "Sora", 700));
        foreach (var participant in participantDbRepository.FindAll())
        {
            Console.WriteLine(participant);
        }
    }

    private static string? GetConnectionStringByName(string name)
    {
        string? result = null;
        var stringSettings = ConfigurationManager.ConnectionStrings[name];
        if (stringSettings != null)
        {
            result = stringSettings.ConnectionString;
        }

        return result;
    }
}