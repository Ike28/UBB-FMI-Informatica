using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Repository;

public interface IUserRepository : IRepository<long, User>
{
    User GetByUsername(string username);
}