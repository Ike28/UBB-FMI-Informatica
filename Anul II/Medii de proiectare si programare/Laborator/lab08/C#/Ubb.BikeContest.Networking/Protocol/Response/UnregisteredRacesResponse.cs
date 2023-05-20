using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Networking.Protocol.Response
{
    [Serializable]
    public class UnregisteredRacesResponse : IResponse
    {
        private readonly List<Race> races;

        public UnregisteredRacesResponse(List<Race> races)
        {
            this.races = races;
        }

        public List<Race> Races { get { return races; } }
    }
}
