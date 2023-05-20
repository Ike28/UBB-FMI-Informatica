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

        public MainController(IContestServices server)
        {
            this.server = server;
        }

        public User CurrentUser
        {
            set { currentUser = value; }
        }

        public void ParticipantAdded(Participant participant)
        {
            UserEventArgs userEvent = new UserEventArgs(UserEvent.NEW_PARTICIPANT, participant);
            Console.WriteLine("Participant event");
            OnUserEvent(userEvent);
        }

        public void RaceEntriesAdded(List<RaceDto> races)
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
            return server.GetRacesWithParticipantCount();
        }

        internal IEnumerable<Team> FindAllTeams()
        {
            return server.FindAllTeams();
        }

        internal void OpenNewParticipantView()
        {
            var newParticipantView = new NewParticipantView(new NewParticipantController(server, currentUser, this));
            newParticipantView.Show();
        }

        internal void Logout()
        {
            server.Logout(currentUser, this);
            var loginForm = new LoginView(new LoginController(server));
            loginForm.Show();
        }

        internal void OpenRegisterView()
        {
            var registerView = new RegisterToRaceView(new RegisterToRaceController(server, currentUser, this));
            registerView.Show();
        }

        internal IEnumerable<Participant> GetParticipantsByTeam(long id)
        {
            return server.GetParticipantsByTeam(id);
        }

        internal IEnumerable<Participant> FindAllParticipants()
        {
            return server.FindAllParticipants();
        }
    }
}
