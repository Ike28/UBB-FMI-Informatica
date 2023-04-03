using System.Collections;
using Ubb.BikeContest.Model;
using Ubb.BikeContest.Repository;
using Ubb.BikeContest.Service.validation;

namespace Ubb.BikeContest.Service;

public class ParticipantService : IParticipantService
{
    private readonly IParticipantRepository _participantRepository;
    private readonly IValidator<long, Participant> _validator;

    public ParticipantService(IParticipantRepository participantRepository)
    {
        _participantRepository = participantRepository;
        _validator = new ParticipantValidator();
    }
    
    public Participant FindById(long id)
    {
        return _participantRepository.FindById(id);
    }

    public IEnumerable<Participant> FindAll()
    {
        return _participantRepository.FindAll();
    }

    public void Save(Participant newEntity)
    {
        _validator.ValidateEntity(newEntity);
        _participantRepository.Save(newEntity);
    }

    public void Delete(long id)
    {
        _participantRepository.Delete(id);
    }

    public void Update(Participant updatedEntity)
    {
        _validator.ValidateEntity(updatedEntity);
        _participantRepository.Update(updatedEntity);
    }

    public IEnumerable<Participant> GetParticipantsByTeam(long teamId)
    {
        return _participantRepository.GetParticipantsByTeam(teamId);
    }

    public Participant GetParticipantByData(Participant participant)
    {
        return _participantRepository.GetParticipantByData(participant);
    }
}