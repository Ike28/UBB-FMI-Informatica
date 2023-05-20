using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Networking.Protocol.Response
{
    [Serializable]
    public class AllTeamsResponse : IResponse
    {
        private readonly List<Team> teams;

        public AllTeamsResponse(List<Team> teams)
        {
            this.teams = teams;
        }

        public List<Team> Teams { get { return teams; } }
    }
}
