using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ubb.BikeContest.Networking.Request
{
    [Serializable]
    public class GetParticipantsByTeamRequest : IRequest
    {
        private readonly long teamId;

        public GetParticipantsByTeamRequest(long teamId)
        {
            this.teamId = teamId;
        }

        public long TeamId { get {  return this.teamId; } }
    }
}
