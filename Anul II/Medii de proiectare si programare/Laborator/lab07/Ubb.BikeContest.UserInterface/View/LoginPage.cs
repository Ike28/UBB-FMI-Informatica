using System.Configuration;
using log4net.Config;
using Ubb.BikeContest.Client.Controller;
using Ubb.BikeContest.Model;
using Ubb.BikeContest.Repository;
using Ubb.BikeContest.Services;
using Ubb.BikeContest.Services.src.Service;

namespace Ubb.BikeContest.UserInterface;

public partial class LoginPage : Form
{
    private readonly LoginController controller;

    public LoginPage(LoginController controller)
    {
        InitializeComponent();
        this.controller = controller;
    }

    private void button1_Click(object sender, EventArgs e)
    {
        string username = usernameBox.Text;
        string passwordToken = Hasher.hash(passwordBox.Text);
        controller.Login(username, "8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918");
        this.Hide();
    }

    private void Form1_Load(object sender, EventArgs e)
    {
        passwordBox.PasswordChar = '*';
    }
}
