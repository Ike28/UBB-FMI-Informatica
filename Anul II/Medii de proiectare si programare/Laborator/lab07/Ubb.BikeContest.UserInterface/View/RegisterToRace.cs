using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms;
using Ubb.BikeContest.Model;
using Ubb.BikeContest.Repository;
using Ubb.BikeContest.Services;
using Ubb.BikeContest.Services.src.Service;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace Ubb.BikeContest.UserInterface
{
    public partial class RegisterToRace : Form
    {
        private IDictionary<string, string> props;
        private IParticipantService participantService;
        private IRaceService raceService;

        public RegisterToRace(IDictionary<string, string> props, Participant current = null)
        {
            InitializeComponent();
            this.props = props;
            IParticipantRepository participantRepository = new ParticipantDbRepository(props);
            IRaceRepository raceRepository = new RaceDbRepository(props);
            IRaceEntryRepository raceEntryRepository = new RaceEntryDbRepository(props, raceRepository, participantRepository);

            participantService = new ParticipantService(participantRepository);
            raceService = new RaceService(raceRepository, raceEntryRepository);
            raceView.View = View.List;
            if (current == null)
            {
                AddParticipants();
            }
            else
            {
                participantBox.Items.Add(current);
            }
            participantBox.SelectedIndex = 0;
            AddRaces();
        }

        private void AddParticipants()
        {
            participantBox.Items.Clear();
            IEnumerable<Participant> participants = participantService.FindAll();
            participantBox.DataSource = participants;
        }

        private void AddRaces()
        {
            raceView.Items.Clear();
            Participant participant = (Participant)participantBox.SelectedItem;
            IEnumerable<Race> races = raceService
                .GetRacesWhereNotRegisteredAndEngineCapacity(participant.Id, participant.EngineCapacity);
            foreach (Race race in races)
            {
                ListViewItem item = new ListViewItem();
                item.Text = race.Name;
                item.Tag = race;
                raceView.Items.Add(item);
            }
            if (races.Count() > 0)
            {
                racesLabel.Text = races.Count() + " RACES FOUND, " + participant.EngineCapacity + "cc CLASS";
            }
            else
            {
                racesLabel.Text = "NO RACES FOUND FOR " + participant.EngineCapacity + "cc CLASS";
            }
        }

        private void confirmButton_Click(object sender, EventArgs e)
        {
            Participant participant = (Participant)participantBox.SelectedItem;
            System.Windows.Forms.ListView.SelectedListViewItemCollection races = raceView.SelectedItems;
            foreach (ListViewItem race in races)
            {
                raceService.SaveRaceEntry(new RaceEntry(participant, (Race)race.Tag));
            }
            //var register = new MainPage(props);
            this.Hide();
            //register.Show();
        }

        private void participantBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            AddRaces();
        }
    }
}
