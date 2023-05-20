using Ubb.BikeContest.Client.Controller;
using Ubb.BikeContest.Model;
using Ubb.BikeContest.Model.data;
using Ubb.BikeContest.Repository;
using Ubb.BikeContest.Services;
using Ubb.BikeContest.Services.src.Service;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.StartPanel;

namespace Ubb.BikeContest.UserInterface
{
    public partial class MainView : Form
    {
        private readonly MainController controller;

        public MainView(MainController controller)
        {
            InitializeComponent();
            controller.updateEvent += UserUpdate;
            this.controller = controller;
            AddRaces();
            AddTeams();
            AddParticipants();
        }

        public void UserUpdate(object sender, UserEventArgs eventArgs)
        {
            if (eventArgs.UserEventType == UserEvent.NEW_PARTICIPANT)
            {
                Participant? participant = eventArgs.Data as Participant;
                if (participant != null)
                {
                    teamBox.BeginInvoke(new UpdateParticipantsCallback(UpdateParticipants), new Object[] { participant });
                }
            }
            if (eventArgs.UserEventType == UserEvent.RACES_MODIFIED)
            {
                IEnumerable<RaceDto>? races = eventArgs.Data as IEnumerable<RaceDto>;
                if (races != null)
                {
                    raceList.BeginInvoke(new UpdateRacesCallback(this.UpdateRaces), new Object[] { races });
                }
            }
        }

        private void AddRaces()
        {
            raceList.View = View.List;
            raceList.Items.Clear();
            IEnumerable<RaceDto> races = controller.GetRacesWithParticipantCount();
            foreach (RaceDto raceDto in races)
            {
                string Name = raceDto.Name;
                if (Name.Length > 40)
                {
                    Name = Name[..40] + "...";
                }
                raceList.Items.Add(Name + ", " + raceDto.Participants + " participants");
            }
        }

        private void UpdateRaces(IEnumerable<RaceDto> races)
        {
            raceList.Items.Clear();
            foreach (RaceDto raceDto in races)
            {
                string Name = raceDto.Name;
                if (Name.Length > 40)
                {
                    Name = Name[..40] + "...";
                }
                raceList.Items.Add(Name + ", " + raceDto.Participants + " participants");
            }
        }

        public delegate void UpdateRacesCallback(IEnumerable<RaceDto> races);

        private void UpdateParticipants(Participant participant)
        {
            if (((Team)teamBox.SelectedItem).Id == participant.Id)
            {
                teamBox.Items.Add(participant);
            }
        }

        public delegate void UpdateParticipantsCallback(Participant participant);

        private void AddTeams()
        {
            IEnumerable<Team> teams = controller.FindAllTeams();
            teamBox.DataSource = teams;
        }

        private void AddParticipants()
        {
            participantsView.View = View.List;
            participantsView.Items.Clear();
            IEnumerable<Participant> participants = controller.FindAllParticipants();
            foreach (Participant participant in participants)
            {
                string Name = participant.FirstName + " " + participant.LastName;
                if (Name.Length > 40)
                {
                    Name = Name[..40] + "...";
                }
                participantsView.Items.Add(Name + ", " + participant.EngineCapacity + "cc");
            }
        }

        private void teamBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            Team team = (Team)teamBox.SelectedItem;
            IEnumerable<Participant> participants = controller.GetParticipantsByTeam(team.Id);
            participantsView.Items.Clear();
            foreach (Participant participant in participants)
            {
                string Name = participant.FirstName + " " + participant.LastName;
                if (Name.Length > 40)
                {
                    Name = Name[..40] + "...";
                }
                participantsView.Items.Add(Name + ", " + participant.EngineCapacity + "cc");
            }
        }

        private void participantButton_Click(object sender, EventArgs e)
        {
            controller.OpenNewParticipantView();
            this.Hide();
        }

        private void logOutButton_Click(object sender, EventArgs e)
        {
            controller.Logout();
            this.Hide();
        }

        private void registerButton_Click(object sender, EventArgs e)
        {
            controller.OpenRegisterView();
            this.Hide();
        }
    }
}
