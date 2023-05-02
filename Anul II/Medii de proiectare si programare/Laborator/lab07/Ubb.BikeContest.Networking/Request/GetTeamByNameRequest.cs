using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ubb.BikeContest.Networking.Request
{
    [Serializable]
    public class GetTeamByNameRequest : IRequest
    {
        private readonly string name;

        public GetTeamByNameRequest(string name)
        {
            this.name = name;
        }

        public virtual string Name
        {
            get { return this.name; }
        }
    }
}
