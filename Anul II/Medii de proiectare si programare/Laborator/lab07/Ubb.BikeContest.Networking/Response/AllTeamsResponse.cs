using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Networking.Response
{
    [Serializable]
    public class AllTeamsResponse : IResponse
    {
        private readonly IEnumerable<Team> teams;

        public AllTeamsResponse(IEnumerable<Team> teams)
        {
            this.teams = teams;
        }

        public IEnumerable<Team> Teams { get { return teams; } }
    }
}
