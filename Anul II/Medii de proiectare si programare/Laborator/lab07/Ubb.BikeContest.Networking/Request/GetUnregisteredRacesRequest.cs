using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ubb.BikeContest.Networking.Request
{
    [Serializable]
    public class GetUnregisteredRacesRequest : IRequest
    {
        private readonly long participantId;
        private readonly int engineCapacity;

        public GetUnregisteredRacesRequest(long participantId, int engineCapacity)
        {
            this.participantId = participantId;
            this.engineCapacity = engineCapacity;
        }

        public virtual long ParticipantId { get { return participantId; } }

        public virtual int EngineCapacity { get {  return engineCapacity; } }
    }
}
