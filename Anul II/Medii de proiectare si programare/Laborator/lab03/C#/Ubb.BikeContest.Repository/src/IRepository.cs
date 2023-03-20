using System.Collections;
using System.Collections.ObjectModel;

namespace Ubb.BikeContest.Repository;

public interface IRepository<TId, TEntity> where TEntity : Ubb.BikeContest.Model.Identifiable<TId>
{
    TEntity Get(TId id);

    IEnumerable Read();

    void Add(TEntity newEntity);

    void Delete(TId id);

    void Update(TEntity updatedEntity);
}