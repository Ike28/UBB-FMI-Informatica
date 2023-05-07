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
    public class LoginController
    {
        private readonly IContestServices server;

        public LoginController(IContestServices server)
        {
            this.server = server;
        }

        public void Login(string username, string passwordToken)
        {
            MainController mainPageController = new MainController(server);
            User user = server.Login(username, passwordToken, mainPageController);
            mainPageController.CurrentUser = user;
            var mainForm = new MainPage(mainPageController);
            mainForm.Show();
        }
    }
}
