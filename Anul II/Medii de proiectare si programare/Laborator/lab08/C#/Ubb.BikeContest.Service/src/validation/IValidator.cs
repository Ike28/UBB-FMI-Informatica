using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Services.validation;

public interface IValidator<TId, TEntity> where TEntity : Identifiable<TId>
{
    void ValidateEntity(TEntity entity);
}