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
    public class LoginController : IMainObserver
    {
        public event EventHandler<UserEventArgs> updateEvent;
        private readonly IContestServices server;

        public LoginController(IContestServices server)
        {
            this.server = server;
        }
        public void ParticipantAdded(Participant participant)
        {
            throw new NotImplementedException();
        }

        public void RaceEntriesAdded(IEnumerable<RaceDto> races)
        {
            throw new NotImplementedException();
        }

        public void Login(string username, string passwordToken)
        {
            User user = server.Login(username, passwordToken, this);
            var mainForm = new MainPage(new MainController(server, user));
            mainForm.Show();
        }
    }
}
