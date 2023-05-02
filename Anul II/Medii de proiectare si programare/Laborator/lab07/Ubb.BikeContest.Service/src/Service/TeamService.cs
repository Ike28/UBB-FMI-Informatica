using System.Collections;
using Ubb.BikeContest.Model;
using Ubb.BikeContest.Repository;
using Ubb.BikeContest.Services.validation;

namespace Ubb.BikeContest.Services.src.Service;

public class TeamService : ITeamService
{
    private readonly ITeamRepository _teamRepository;
    private readonly IValidator<long, Team> _validator;

    public TeamService(ITeamRepository teamRepository)
    {
        _teamRepository = teamRepository;
        _validator = new TeamValidator();
    }

    public Team FindById(long id)
    {
        return _teamRepository.FindById(id);
    }

    public IEnumerable<Team> FindAll()
    {
        return _teamRepository.FindAll();
    }

    public void Save(Team newEntity)
    {
        _validator.ValidateEntity(newEntity);
        _teamRepository.Save(newEntity);
    }

    public void Delete(long id)
    {
        _teamRepository.Delete(id);
    }

    public void Update(Team updatedEntity)
    {
        _validator.ValidateEntity(updatedEntity);
        _teamRepository.Update(updatedEntity);
    }

    public Team GetTeamByName(string teamName)
    {
        return _teamRepository.GetTeamByName(teamName);
    }
}