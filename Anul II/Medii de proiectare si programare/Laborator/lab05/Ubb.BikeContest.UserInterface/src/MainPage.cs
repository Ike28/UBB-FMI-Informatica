using Ubb.BikeContest.Model;
using Ubb.BikeContest.Model.data;
using Ubb.BikeContest.Repository;
using Ubb.BikeContest.Service;

namespace Ubb.BikeContest.UserInterface
{
    public partial class MainPage : Form
    {

        private IDictionary<string, string> props;
        private IRaceService raceService;
        private ITeamService teamService;
        private IParticipantService participantService;
        public MainPage(IDictionary<string, string> props)
        {
            InitializeComponent();
            this.props = props;
            IRaceRepository raceRepository = new RaceDbRepository(props);
            IParticipantRepository participantRepository = new ParticipantDbRepository(props);
            IRaceEntryRepository raceEntryRepository = new RaceEntryDbRepository(props, raceRepository, participantRepository);
            this.raceService = new RaceService(raceRepository, raceEntryRepository);
            this.teamService = new TeamService(new TeamDbRepository(props));
            this.participantService = new ParticipantService(participantRepository);
            AddRaces();
            AddTeams();
            AddParticipants();
        }

        private void AddRaces()
        {
            raceList.View = View.List;
            raceList.Items.Clear();
            IEnumerable<RaceDto> races = raceService.GetRacesWithParticipantCount();
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

        private void AddTeams()
        {
            IEnumerable<Team> teams = teamService.FindAll();
            teamBox.DataSource = teams;
        }

        private void AddParticipants()
        {
            participantsView.View = View.List;
            participantsView.Items.Clear();
            IEnumerable<Participant> participants = participantService.FindAll();
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
            IEnumerable<Participant> participants = participantService.GetParticipantsByTeam(team.Id);
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
            var newParticipantForm = new NewParticipant(props);
            this.Hide();
            newParticipantForm.Show();
        }

        private void logOutButton_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void registerButton_Click(object sender, EventArgs e)
        {
            var register = new RegisterToRace(props);
            this.Hide();
            register.Show();
        }
    }
}
