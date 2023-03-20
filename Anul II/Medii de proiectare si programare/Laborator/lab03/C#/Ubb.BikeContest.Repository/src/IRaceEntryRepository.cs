using System.Collections;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Repository;

public interface IRaceEntryRepository : IRepository<long, RaceEntry>
{
    IEnumerable GetEntriesByRace(long raceId);
}