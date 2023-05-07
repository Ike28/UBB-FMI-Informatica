using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Networking.Response
{
    [Serializable]
    public class GetParticipantsByTeamResponse : IResponse
    {
        private readonly List<Participant> teamParticipants;

        public GetParticipantsByTeamResponse(List<Participant> teamParticipants)
        {
            this.teamParticipants = teamParticipants;
        }

        public List<Participant> Participants { get { return teamParticipants; } }
    }
}
