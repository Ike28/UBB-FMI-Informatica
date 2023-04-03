using System.Collections;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Repository;

public interface IParticipantRepository : IRepository<long, Participant>
{
    IEnumerable<Participant> GetParticipantsByTeam(long teamId);

    Participant GetParticipantByData(Participant participant);
}