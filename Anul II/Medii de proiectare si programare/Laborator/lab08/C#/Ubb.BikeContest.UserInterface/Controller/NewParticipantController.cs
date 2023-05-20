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
    public class NewParticipantController
    {
        private readonly IContestServices server;
        private readonly User currentUser;
        private readonly MainController mainController;

        public NewParticipantController(IContestServices server, User currentUser, MainController mainController)
        {
            this.server = server;
            this.currentUser = currentUser;
            this.mainController = mainController;
        }

        internal IEnumerable<Team> FindAllTeams()
        {
            return server.FindAllTeams();
        }

        internal void SaveParticipant(Participant newParticipant)
        {
            server.SaveParticipant(newParticipant);
            OpenMainView();
        }

        internal void OpenMainView()
        {
            var mainPage = new MainView(mainController);
            mainPage.Show();
        }
    }
}
