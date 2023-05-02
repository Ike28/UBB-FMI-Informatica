using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Networking.Response
{
    [Serializable]
    public class ParticipantResponse : IResponse
    {
        private readonly Participant participant;

        public ParticipantResponse(Participant participant)
        {
            this.participant = participant;
        }

        public Participant Participant { get { return participant; } }
    }
}
