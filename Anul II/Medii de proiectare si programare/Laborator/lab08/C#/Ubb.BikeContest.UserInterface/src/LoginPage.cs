using System.Configuration;
using log4net.Config;
using Ubb.BikeContest.Model;
using Ubb.BikeContest.Repository;
using Ubb.BikeContest.Services;
using Ubb.BikeContest.Services.src.Service;

namespace Ubb.BikeContest.UserInterface;

public partial class LoginPage : Form
{
    private IDictionary<string, string> props;
    private IUserService userService;
    public LoginPage()
    {
        InitializeComponent();
    }

    private void button1_Click(object sender, EventArgs e)
    {
        this.Hide();
        var mainForm = new MainPage(props);
        mainForm.Show();
    }

    private void Form1_Load(object sender, EventArgs e)
    {
        XmlConfigurator.Configure(new FileInfo("app.config"));
        XmlConfigurator.Configure(new FileInfo("log4net.config"));
        Console.WriteLine("Configuration Settings for DB {0}", GetConnectionStringByName("bikeContestDB"));
        props = new SortedList<string, string?>();
        props.Add("ConnectionString", GetConnectionStringByName("bikeContestDB"));

        userService = new UserService(new UserDbRepository(props));
        passwordBox.PasswordChar = '*';
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
