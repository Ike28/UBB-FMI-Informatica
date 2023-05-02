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
            throw new NotImplementedException();
        }

        public IEnumerable<Team> FindAllTeams()
        {
            throw new NotImplementedException();
        }

        public IEnumerable<Participant> GetParticipantsByTeam(long id)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<RaceDto> GetRacesWithParticipantCount()
        {
            throw new NotImplementedException();
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

        /*public void sendMessage(Message message)  {
            String id_receiver=message.Receiver.Id;
        
            if (loggedClients.ContainsKey(id_receiver))  {     //the receiver is logged in
                IChatObserver receiverClient=loggedClients[id_receiver];
                receiverClient.messageReceived(message);
            }
            else
                throw new ChatException("User "+id_receiver+" not logged in.");
        }*/

        public void Logout(User user, IMainObserver client) {
            IMainObserver localClient=loggedClients[user.Username];
            if (localClient == null)
            {
                throw new ContestDataException("User " + user.Id + " is not logged in.");
            }
            loggedClients.Remove(user.Username);
        }
    }
}
