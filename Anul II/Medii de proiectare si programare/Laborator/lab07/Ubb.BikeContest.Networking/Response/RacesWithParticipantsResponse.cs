using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model.data;

namespace Ubb.BikeContest.Networking.Response
{
    [Serializable]
    public class RacesWithParticipantsResponse : IResponse
    {
        private readonly List<RaceDto> races;

        public RacesWithParticipantsResponse(List<RaceDto> races)
        {
            this.races = races;
        }

        public List<RaceDto> Races { get { return races; } }
    }
}
