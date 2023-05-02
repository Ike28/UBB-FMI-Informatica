using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ubb.BikeContest.Networking.Request
{
    [Serializable]
    public class GetRaceByNameRequest : IRequest
    {
        private readonly string raceName;

        public GetRaceByNameRequest(string raceName)
        {
            this.raceName = raceName;
        }

        public virtual string RaceName
        {
            get { return raceName; }
        }
    }
}
