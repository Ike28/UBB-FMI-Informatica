using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Ubb.BikeContest.Model;
using Ubb.BikeContest.Model.data;

namespace Ubb.BikeContest.Services
{
    public interface IContestServices
    {
        User Login(string username, string passwordToken, IMainObserver client);
        void Logout(User user, IMainObserver client);
        List<RaceDto> GetRacesWithParticipantCount();
        List<Team> FindAllTeams();
        List<Participant> GetParticipantsByTeam(long id);
        List<Participant> FindAllParticipants();
        void SaveRaceEntries(List<RaceEntry> newEntities);
        void SaveParticipant(Participant newEntity);
        List<Race> GetRacesWhereNotRegisteredAndEngineCapacity(long participantId, int engineCapacity);
    }
}
