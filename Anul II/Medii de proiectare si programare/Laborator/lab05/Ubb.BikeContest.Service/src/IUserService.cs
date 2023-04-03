using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Service;

public interface IUserService : IService<long, User>
{
    User GetLogin(string username, string password);
}