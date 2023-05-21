using log4net.Config;
using System.Configuration;
using Ubb.BikeContest.Networking;
using Ubb.BikeContest.Repository;
using Ubb.BikeContest.Server;
using Ubb.BikeContest.Services.src.Service;

namespace Ubb.BikeContest.Services
{
    class StartServer
    {
        static void Main(string[] args)
        {
            IDictionary<string, string> props = new SortedList<string, string>();
            XmlConfigurator.Configure(new FileInfo("app.config"));
            string? connectionString = GetConnectionStringByName("bikeContestDB");

            if (connectionString == null)
            {
                Console.WriteLine("Cannot start server: null connection string");
                return;
            }
            props.Add("ConnectionString", connectionString);

            IUserRepository userRepository = new UserDbRepository(props);
            IRaceRepository raceRepository = new RaceDbRepository(props);
            IParticipantRepository participantRepository = new ParticipantDbRepository(props);
            IRaceEntryRepository raceEntryRepository = new RaceEntryDbRepository(props, raceRepository, participantRepository);
            ITeamRepository teamRepository = new TeamDbRepository(props);

            IUserService userService = new UserService(userRepository);
            IParticipantService participantService = new ParticipantService(participantRepository);
            ITeamService teamService = new TeamService(teamRepository);
            IRaceService raceService = new RaceService(raceRepository, raceEntryRepository);

            IContestServices server = new ContestServices(userService, participantService, raceService, teamService);

            IServer scs = new ProtocolBufferServer("127.0.0.1", 55556, server);
            scs.Start();
            Console.WriteLine("Server started ...");
            Console.ReadLine();
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
}
