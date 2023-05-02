using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ubb.BikeContest.Networking.Request
{
    [Serializable]
    public class GetEntriesByRaceRequest : IRequest
    {
        private readonly long raceId;

        public GetEntriesByRaceRequest(long raceId)
        {
            this.raceId = raceId;
        }

        public virtual long RaceId
        {
           get { return raceId; }
        }
    }
}
