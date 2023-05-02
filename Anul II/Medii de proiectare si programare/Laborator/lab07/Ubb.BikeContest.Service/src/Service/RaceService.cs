using System.Collections;
using Ubb.BikeContest.Model;
using Ubb.BikeContest.Model.data;
using Ubb.BikeContest.Repository;
using Ubb.BikeContest.Services.validation;

namespace Ubb.BikeContest.Services.src.Service;

public class RaceService : IRaceService
{
    private readonly IRaceRepository _raceRepository;
    private readonly IRaceEntryRepository _raceEntryRepository;
    private readonly IValidator<long, Race> _validator;

    public RaceService(IRaceRepository raceRepository, IRaceEntryRepository raceEntryRepository)
    {
        _raceRepository = raceRepository;
        _raceEntryRepository = raceEntryRepository;
        _validator = new RaceValidator();
    }

    public Race FindById(long id)
    {
        return _raceRepository.FindById(id);
    }

    public IEnumerable<Race> FindAll()
    {
        return _raceRepository.FindAll();
    }

    public void Save(Race newEntity)
    {
        _validator.ValidateEntity(newEntity);
        _raceRepository.Save(newEntity);
    }

    public void Delete(long id)
    {
        _raceRepository.Delete(id);
    }

    public void Update(Race updatedEntity)
    {
        _validator.ValidateEntity(updatedEntity);
        _raceRepository.Update(updatedEntity);
    }

    public Race GetRaceByName(string name)
    {
        return _raceRepository.GetRaceByName(name);
    }

    public IEnumerable<RaceEntry> GetEntriesByRace(long raceId)
    {
        return _raceEntryRepository.GetEntriesByRace(raceId);
    }

    public void DeleteByIds(long participantId, long raceId)
    {
        throw new NotImplementedException();
    }

    public IEnumerable<Race> GetRacesByEngineCapacity(int engineCapacity)
    {
        return _raceRepository.GetRacesByEngineCapacity(engineCapacity);
    }

    public IEnumerable<RaceDto> GetRacesWithParticipantCount()
    {
        IEnumerable<Race> races = _raceRepository.FindAll();
        IList<RaceDto> result = new List<RaceDto>();
        foreach (var race in races)
        {
            result.Add(new RaceDto(race.Name, race.EngineCapacity,
                _raceEntryRepository.GetEntriesByRace(race.Id).Count()));
        }
        return result;
    }

    public void SaveRaceEntry(RaceEntry newEntity)
    {
        _raceEntryRepository.Save(newEntity);
    }

    public IEnumerable<Race> GetRacesWhereNotRegisteredAndEngineCapacity(long participantId, int engineCapacity)
    {
        return _raceEntryRepository.GetRacesWhereNotRegisteredAndEngineCapacity(participantId, engineCapacity);
    }
}