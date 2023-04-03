using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Ubb.BikeContest.Model;
using Ubb.BikeContest.Repository;
using Ubb.BikeContest.Service;

namespace Ubb.BikeContest.UserInterface
{
    public partial class NewParticipant : Form
    {
        private IDictionary<string, string> props;
        private IParticipantService participantService;
        private ITeamService teamService;

        public NewParticipant(IDictionary<string, string> props)
        {
            InitializeComponent();
            this.props = props;
            this.participantService = new ParticipantService(new ParticipantDbRepository(props));
            this.teamService = new TeamService(new TeamDbRepository(props));
            AddTeams();
        }

        private void AddTeams()
        {
            IEnumerable<Team> teams = teamService.FindAll();
            teamBox.DataSource = teams;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string firstname = firstnameField.Text;
            string lastname = lastnameField.Text;
            int engineCapacity = (int)engineField.Value;
            Team team = (Team)teamBox.SelectedItem;

            if (firstname != "" && lastname != "" && engineCapacity > 0)
            {
                Participant newParticipant = new Participant(firstname, lastname, engineCapacity);
                newParticipant.TeamId = team.Id;
                participantService.Save(newParticipant);

                var register = new RegisterToRace(props);
                this.Hide();
                register.Show();
            }
            else
            {
                var mainForm = new MainPage(props);
                this.Hide();
                mainForm.Show();
            }
        }
    }
}
