using System.Collections;

namespace Ubb.BikeContest.Repository;

public interface IRepository<TId, TEntity> where TEntity : Model.Identifiable<TId>
{
    TEntity FindById(TId id);

    IEnumerable FindAll();

    void Save(TEntity newEntity);

    void Delete(TId id);

    void Update(TEntity updatedEntity);
}