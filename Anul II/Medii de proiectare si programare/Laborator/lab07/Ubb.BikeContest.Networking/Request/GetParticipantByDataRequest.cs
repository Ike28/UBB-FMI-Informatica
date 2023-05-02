using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Networking.Request
{
    [Serializable]
    public class GetParticipantByDataRequest : IRequest
    {
        private readonly Participant participant;

        public GetParticipantByDataRequest(Participant participant)
        {
            this.participant = participant;
        }

        public virtual Participant Participant 
        { 
            get { return participant; } 
        }
    }
}
