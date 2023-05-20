using System.Collections;
using Ubb.BikeContest.Model;

namespace Ubb.BikeContest.Service;

public interface IService<TId, TEntity> where TEntity : Identifiable<TId>
{
    TEntity FindById(TId id);

    IEnumerable<TEntity> FindAll();

    void Save(TEntity newEntity);

    void Delete(TId id);

    void Update(TEntity updatedEntity);
}