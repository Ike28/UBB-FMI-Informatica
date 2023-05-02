using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ubb.BikeContest.Networking.Request
{
    [Serializable]
    public class GetRacesByEngineCapacityRequest : IRequest
    {
        private readonly int engineCapacity;

        public GetRacesByEngineCapacityRequest(int engineCapacity)
        {
            this.engineCapacity = engineCapacity;
        }

        public virtual int EngineCapacity { get {  return engineCapacity; } }
    }
}
