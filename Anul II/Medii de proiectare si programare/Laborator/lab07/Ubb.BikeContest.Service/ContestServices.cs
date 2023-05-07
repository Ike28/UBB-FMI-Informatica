using Ubb.BikeContest.Model;
using Ubb.BikeContest.Model.data;
using Ubb.BikeContest.Services;
using Ubb.BikeContest.Services.src.Exceptions;
using Ubb.BikeContest.Services.src.Service;

namespace Ubb.BikeContest.Services
{
    public class ContestServices : IContestServices
    {
        private readonly IUserService userService;
        private readonly IParticipantService participantService;
        private readonly IRaceService raceService;
        private readonly ITeamService teamService;

        private readonly IDictionary <string, IMainObserver> loggedClients;


        public ContestServices(IUserService userService, IParticipantService participantService,
            IRaceService raceService, ITeamService teamService)
        {
            loggedClients = new Dictionary<string, IMainObserver>();
            this.userService = userService;
            this.participantService = participantService;
            this.raceService = raceService;
            this.teamService = teamService;
        }

        public IEnumerable<Participant> FindAllParticipants()
        {
            return participantService.FindAll();
        }

        public IEnumerable<Team> FindAllTeams()
        {
            return teamService.FindAll();
        }

        public IEnumerable<Participant> GetParticipantsByTeam(long id)
        {
            return participantService.GetParticipantsByTeam(id);
        }

        public IEnumerable<RaceDto> GetRacesWithParticipantCount()
        {
            return raceService.GetRacesWithParticipantCount();
        }

        public User Login(string username, string passwordToken, IMainObserver client)  {
            User? foundUser = userService.GetLogin(username, passwordToken);
            if (foundUser != null)
            {
                if (loggedClients.ContainsKey(foundUser.Username))
                {
                    throw new ContestDataException("User already logged in.");
                }
                loggedClients[foundUser.Username] = client;
                return foundUser;
            }
            else
            {
                throw new ContestDataException("Authentication failed.");
            }
        }

        public void Logout(User user, IMainObserver client) {
            IMainObserver localClient=loggedClients[user.Username];
            if (localClient == null)
            {
                throw new ContestDataException("User " + user.Id + " is not logged in.");
            }
            loggedClients.Remove(user.Username);
        }

        public void SaveRaceEntries(IEnumerable<RaceEntry> newEntities)
        {
            foreach (RaceEntry entity in newEntities)
            {
                raceService.SaveRaceEntry(entity);
            }
            foreach (IMainObserver client in loggedClients.Values)
            {
                client.RaceEntriesAdded(GetRacesWithParticipantCount());
            }
        }

        public IEnumerable<Race> GetRacesWhereNotRegisteredAndEngineCapacity(long participantId, int engineCapacity)
        {
            return raceService.GetRacesWhereNotRegisteredAndEngineCapacity(participantId, engineCapacity);
        }

        public void SaveParticipant(Participant newEntity)
        {
            participantService.Save(newEntity);
            foreach (IMainObserver client in loggedClients.Values)
            {
                client.ParticipantAdded(newEntity);
            }
        }
    }
}
