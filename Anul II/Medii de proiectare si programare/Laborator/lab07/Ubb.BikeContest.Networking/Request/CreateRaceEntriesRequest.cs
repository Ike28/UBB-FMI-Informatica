using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Networking.Request
{
    [Serializable]
    public class CreateRaceEntriesRequest : IRequest
    {
        private readonly IEnumerable<RaceEntry> raceEntries;

        public CreateRaceEntriesRequest(IEnumerable<RaceEntry> raceEntries)
        {
            this.raceEntries = raceEntries;
        }

        public virtual IEnumerable<RaceEntry> RaceEntries
        {
            get { return raceEntries; }
        }
    }
}
