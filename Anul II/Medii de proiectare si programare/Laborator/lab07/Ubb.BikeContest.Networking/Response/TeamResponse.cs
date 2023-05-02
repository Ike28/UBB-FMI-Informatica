using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Networking.Response
{
    [Serializable]
    public class TeamResponse : IResponse
    {
        private readonly Team team;

        public TeamResponse(Team team)
        {
            this.team = team;
        }

        public Team Team
        {
            get { return team; }
        } 
    }
}
