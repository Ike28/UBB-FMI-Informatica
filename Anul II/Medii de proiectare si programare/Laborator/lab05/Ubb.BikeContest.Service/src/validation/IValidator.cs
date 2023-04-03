using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Service.validation;

public interface IValidator<TId, TEntity> where TEntity : Identifiable<TId>
{
    void ValidateEntity(TEntity entity);
}