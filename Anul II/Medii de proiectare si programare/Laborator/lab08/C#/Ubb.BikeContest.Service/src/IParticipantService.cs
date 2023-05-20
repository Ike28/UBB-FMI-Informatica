using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Service;

public interface IParticipantService : IService<long, Participant>
{
    IEnumerable<Participant> GetParticipantsByTeam(long teamId);

    Participant GetParticipantByData(Participant participant);
}