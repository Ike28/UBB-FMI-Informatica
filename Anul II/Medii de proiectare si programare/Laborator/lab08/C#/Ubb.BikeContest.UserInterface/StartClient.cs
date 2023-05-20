using log4net.Config;
using System.Configuration;
using Ubb.BikeContest.Client.Controller;
using Ubb.BikeContest.Networking;
using Ubb.BikeContest.Networking.ProtocolBuffers;
using Ubb.BikeContest.Services;

namespace Ubb.BikeContest.UserInterface;

static class StartClient
{
    [STAThread]
    static void Main()
    {
        ApplicationConfiguration.Initialize();
        IDictionary<string, string> props = new SortedList<string, string>();
        XmlConfigurator.Configure(new FileInfo("client.config"));

        IContestServices server = new ProtobufServicesProxy("127.0.0.1", 55556);
        LoginController loginController = new LoginController(server);
        Application.Run(new LoginView(loginController));
    }
}