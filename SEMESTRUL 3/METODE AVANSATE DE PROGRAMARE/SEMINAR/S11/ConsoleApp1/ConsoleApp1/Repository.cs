namespace ConsoleApp1;

interface IRepository<ID, E> where E : Entity<ID>
{
    E FindOne(ID id);
    IEnumerable<E> FindAll();
    E Save(E entity);
    E Delete(ID id);
    E Update(E entity);
}