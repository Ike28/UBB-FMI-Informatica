using System.Collections;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Repository;

public interface IRaceEntryRepository : IRepository<long, RaceEntry>
{
    IEnumerable<RaceEntry> GetEntriesByRace(long raceId);

    IEnumerable<Race> GetRacesWhereNotRegisteredAndEngineCapacity(long participantId, int engineCapacity);
}