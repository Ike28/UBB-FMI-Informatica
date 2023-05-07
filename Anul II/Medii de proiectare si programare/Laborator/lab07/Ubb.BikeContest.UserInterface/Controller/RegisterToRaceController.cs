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
    public class RegisterToRaceController
    {
        private readonly IContestServices server;
        private User currentUser;
        private MainController mainController;

        public RegisterToRaceController(IContestServices server, User currentUser, MainController mainController)
        {
            this.server = server;
            this.currentUser = currentUser;
            this.mainController = mainController;
        }

        internal IEnumerable<Participant> FindAllParticipants()
        {
            return server.FindAllParticipants();
        }

        internal void SaveRaceEntry(RaceEntry raceEntry)
        {
            server.SaveRaceEntry(raceEntry);
        }

        internal IEnumerable<Race> GetRacesWhereNotRegisteredAndEngineCapacity(long id, int engineCapacity)
        {
            return server.GetRacesWhereNotRegisteredAndEngineCapacity(id, engineCapacity);
        }

        internal void OpenMainView()
        {
            var mainPage = new MainPage(mainController);
            mainPage.Show();
        }
    }
}
