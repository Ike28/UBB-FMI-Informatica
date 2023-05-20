using System.Collections;
using Ubb.BikeContest.Model;
using Ubb.BikeContest.Repository;
using Ubb.BikeContest.Services.validation;

namespace Ubb.BikeContest.Services.src.Service;

public class UserService : IUserService
{
    private readonly IUserRepository _userRepository;
    private readonly IValidator<long, User> _validator;

    public UserService(IUserRepository userRepository)
    {
        _userRepository = userRepository;
        _validator = new UserValidator();
    }

    public User FindById(long id)
    {
        return _userRepository.FindById(id);
    }

    public IEnumerable<User> FindAll()
    {
        return _userRepository.FindAll();
    }

    public void Save(User newEntity)
    {
        _validator.ValidateEntity(newEntity);
        _userRepository.Save(newEntity);
    }

    public void Delete(long id)
    {
        _userRepository.Delete(id);
    }

    public void Update(User updatedEntity)
    {
        _userRepository.Update(updatedEntity);
    }

    public User GetLogin(string username, string password)
    {
        return _userRepository.GetByUsernameAndPassword(username, password);
    }
}