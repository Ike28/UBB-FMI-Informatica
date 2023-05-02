using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Networking.Response
{
    [Serializable]
    public class RaceByNameResponse : IResponse
    {
        private readonly Race race;

        public RaceByNameResponse(Race race)
        {
            this.race = race;
        }

        public Race Race { get { return race; } }
    }
}
