using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;
using Ubb.BikeContest.Model.data;
using Ubb.BikeContest.Services;
using Ubb.BikeContest.UserInterface;

namespace Ubb.BikeContest.Client.Controller
{
    public class MainController : IMainObserver
    {
        public event EventHandler<UserEventArgs> updateEvent;
        private readonly IContestServices server;
        private User currentUser;

        public MainController(IContestServices server, User currentUser)
        {
            this.server = server;
            this.currentUser = currentUser;
        }

        public void ParticipantAdded(Participant participant)
        {
            UserEventArgs userEvent = new UserEventArgs(UserEvent.NEW_PARTICIPANT, participant);
            Console.WriteLine("Participant event");
            OnUserEvent(userEvent);
        }

        public void RaceEntriesAdded(IEnumerable<RaceDto> races)
        {
            UserEventArgs userEvent = new UserEventArgs(UserEvent.RACES_MODIFIED, races);
            Console.WriteLine("Race entries event");
            OnUserEvent(userEvent);
        }
        protected virtual void OnUserEvent(UserEventArgs e)
        {
            if (updateEvent == null)
            {
                return;
            }

            updateEvent(this, e);
            Console.WriteLine("Update event called");
        }

        internal IEnumerable<RaceDto> GetRacesWithParticipantCount()
        {
            throw new NotImplementedException();
        }

        internal IEnumerable<Team> FindAllTeams()
        {
            throw new NotImplementedException();
        }

        internal void NewParticipant()
        {
            throw new NotImplementedException();
        }

        internal void Logout()
        {
            server.Logout(currentUser, this);
            var loginForm = new LoginPage(new LoginController(server));
            loginForm.Show();
        }

        internal void RegisterToRace()
        {
            throw new NotImplementedException();
        }

        internal IEnumerable<Participant> GetParticipantsByTeam(long id)
        {
            throw new NotImplementedException();
        }

        internal IEnumerable<Participant> FindAllParticipants()
        {
            throw new NotImplementedException();
        }
    }
}
