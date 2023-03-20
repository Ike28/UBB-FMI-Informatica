using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Repository;

public interface IRaceRepository : IRepository<long, Race>
{
    Race GetRaceByName(string name);
}