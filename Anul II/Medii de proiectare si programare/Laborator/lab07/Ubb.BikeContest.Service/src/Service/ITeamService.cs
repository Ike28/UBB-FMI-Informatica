using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Services.src.Service;

public interface ITeamService : IService<long, Team>
{
    Team GetTeamByName(string teamName);
}