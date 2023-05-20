using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Networking.Protocol.Request
{
    [Serializable]
    public class CreateParticipantRequest : IRequest
    {
        private readonly Participant participant;

        public CreateParticipantRequest(Participant participant)
        {
            this.participant = participant;
        }

        public virtual Participant Participant
        {
            get { return participant; }
        }
    }
}
