using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Service;

public interface ITeamService : IService<long, Team>
{
    Team GetTeamByName(string teamName);
}