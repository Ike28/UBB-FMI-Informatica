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
        IEnumerable<RaceDto> GetRacesWithParticipantCount();
        IEnumerable<Team> FindAllTeams();
        IEnumerable<Participant> GetParticipantsByTeam(long id);
        IEnumerable<Participant> FindAllParticipants();
    }
}
