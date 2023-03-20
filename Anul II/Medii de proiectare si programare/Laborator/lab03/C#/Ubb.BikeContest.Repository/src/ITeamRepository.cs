using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Repository;

public interface ITeamRepository : IRepository<long, Team>
{
    Team GetTeamByName(string teamName);
}