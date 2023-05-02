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
        private readonly IEnumerable<Participant> teamParticipants;

        public GetParticipantsByTeamResponse(IEnumerable<Participant> teamParticipants)
        {
            this.teamParticipants = teamParticipants;
        }

        public IEnumerable<Participant> Participants { get { return teamParticipants; } }
    }
}
