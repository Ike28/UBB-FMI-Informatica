using log4net.Config;
using System;
using System.Configuration;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Repository;

public class BikeContest
{
    public static void Main(string[] args)
    {
        XmlConfigurator.Configure(new System.IO.FileInfo("app.config"));
        Console.WriteLine("Configuration Settings for DB {0}",GetConnectionStringByName("bikeContestDB"));
        IDictionary<String, string> props = new SortedList<String, String>();
        props.Add("ConnectionString", GetConnectionStringByName("bikeContestDB"));

        ParticipantDBRepository participantDbRepository = new ParticipantDBRepository(props);
        participantDbRepository.Add(new Participant("Mihai", "Sora", 700));
        foreach (var participant in participantDbRepository.Read())
        {
            Console.WriteLine(participant);
        }
    }

    private static string GetConnectionStringByName(string name)
    {
        string result = null;
        ConnectionStringSettings stringSettings = ConfigurationManager.ConnectionStrings[name];
        if (stringSettings != null)
        {
            result = stringSettings.ConnectionString;
        }

        return result;
    }
}