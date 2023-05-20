using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Networking.Protocol.Request
{
    [Serializable]
    public class CreateRaceEntriesRequest : IRequest
    {
        private readonly List<RaceEntry> raceEntries;

        public CreateRaceEntriesRequest(List<RaceEntry> raceEntries)
        {
            this.raceEntries = raceEntries;
        }

        public virtual List<RaceEntry> RaceEntries
        {
            get { return raceEntries; }
        }
    }
}
