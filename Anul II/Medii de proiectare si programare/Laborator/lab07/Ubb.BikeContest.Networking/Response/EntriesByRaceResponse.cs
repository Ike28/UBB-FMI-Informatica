using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Networking.Response
{
    [Serializable]
    public class EntriesByRaceResponse : IResponse
    {
        private readonly IEnumerable<RaceEntry> raceEntries;

        public EntriesByRaceResponse(IEnumerable<RaceEntry> raceEntries)
        {
            this.raceEntries = raceEntries;
        }

        public IEnumerable<RaceEntry> RaceEntries { get { return raceEntries; } }
    }
}
