using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model.data;

namespace Ubb.BikeContest.Networking.Response
{
    [Serializable]
    public class UpdatedRacesResponse : UpdateResponse
    {
        private readonly List<RaceDto> races;

        public UpdatedRacesResponse(List<RaceDto> races)
        {
            this.races = races;
        }

        public List<RaceDto> Races { get { return races; } }
    }
}
