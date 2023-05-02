using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Networking.Response
{
    [Serializable]
    public class AllParticipantsResponse : IResponse
    {
        private readonly IEnumerable<Participant> participants;

        public AllParticipantsResponse(IEnumerable<Participant> participants)
        {
            this.participants = participants;
        }

        public virtual IEnumerable<Participant> Participants { get { return participants; } }
    }
}
