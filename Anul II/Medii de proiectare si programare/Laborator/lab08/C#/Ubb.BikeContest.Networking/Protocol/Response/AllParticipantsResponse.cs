using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Networking.Protocol.Response
{
    [Serializable]
    public class AllParticipantsResponse : IResponse
    {
        private readonly List<Participant> participants;

        public AllParticipantsResponse(List<Participant> participants)
        {
            this.participants = participants;
        }

        public virtual List<Participant> Participants { get { return participants; } }
    }
}
