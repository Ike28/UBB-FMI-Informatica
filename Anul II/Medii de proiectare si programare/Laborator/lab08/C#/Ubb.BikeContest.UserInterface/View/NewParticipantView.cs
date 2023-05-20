using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Ubb.BikeContest.Client.Controller;
using Ubb.BikeContest.Model;
using Ubb.BikeContest.Repository;
using Ubb.BikeContest.Services;
using Ubb.BikeContest.Services.src.Service;

namespace Ubb.BikeContest.UserInterface
{
    public partial class NewParticipantView : Form
    {

        private readonly NewParticipantController controller;

        public NewParticipantView(NewParticipantController controller)
        {
            InitializeComponent();
            this.controller = controller;
            AddTeams();
        }

        private void AddTeams()
        {
            IEnumerable<Team> teams = controller.FindAllTeams();
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
                controller.SaveParticipant(newParticipant);
            }
            else
            {
                controller.OpenMainView();
            }
            this.Hide();
        }
    }
}
