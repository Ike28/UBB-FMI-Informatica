using Ubb.BikeContest.Model;
using Ubb.BikeContest.Model.data;

namespace Ubb.BikeContest.Service;

public interface IRaceService : IService<long, Race>
{
    
    Race GetRaceByName(string name);

    IEnumerable<RaceEntry> GetEntriesByRace(long raceId);

    void DeleteByIds(long participantId, long raceId);

    IEnumerable<Race> GetRacesByEngineCapacity(int engineCapacity);

    IEnumerable<RaceDto> GetRacesWithParticipantCount();

    void SaveRaceEntry(RaceEntry newEntity);

    IEnumerable<Race> GetRacesWhereNotRegisteredAndEngineCapacity(long participantId, int engineCapacity);
}