using System.Collections.ObjectModel;

namespace Ubb.BikeContest.Repository;

public interface IRepository<TID, TEntity> where TEntity : Ubb.BikeContest.Model.Identifiable<TID>
{
    TID Get(TID id);

    Collection<TEntity> Read();

    void Add(TEntity newEntity);

    void Delete(TID id);

    void Update(TEntity updatedEntity);
}