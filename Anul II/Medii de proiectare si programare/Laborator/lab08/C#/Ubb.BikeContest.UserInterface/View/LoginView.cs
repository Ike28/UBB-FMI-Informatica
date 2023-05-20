using System.Configuration;
using log4net.Config;
using Ubb.BikeContest.Client.Controller;
using Ubb.BikeContest.Model;
using Ubb.BikeContest.Repository;
using Ubb.BikeContest.Services;
using Ubb.BikeContest.Services.src.Service;

namespace Ubb.BikeContest.UserInterface;

public partial class LoginView : Form
{
    private readonly LoginController controller;

    public LoginView(LoginController controller)
    {
        InitializeComponent();
        this.controller = controller;
    }

    private void button1_Click(object sender, EventArgs e)
    {
        string username = usernameBox.Text;
        string passwordToken = Hasher.Hash(passwordBox.Text);
        controller.Login(username, passwordToken);
        this.Hide();
    }

    private void Form1_Load(object sender, EventArgs e)
    {
        passwordBox.PasswordChar = '*';
    }
}
