using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Networking.Response
{
    [Serializable]
    public class RacesByCapacityResponse : IResponse
    {
        private readonly IEnumerable<Race> races;

        public RacesByCapacityResponse(IEnumerable<Race> races)
        {
            this.races = races;
        }

        public IEnumerable<Race> Races { get { return races; } }
    }
}
