namespace ConsoleApp1;

public class InMemoryRepository<ID, E> : IRepository<ID, E> where E : Entity<ID>
{
    protected IValidator<E> Validator;
    protected IDictionary<ID, E> Entities = new Dictionary<ID, E>();

    public InMemoryRepository(IValidator<E> validator)
    {
        Validator = validator;
    }

    public IEnumerable<E> FindAll()
    {
        return Entities.Values.ToList();
    }

    public E Save(E entity)
    {
        if (entity == null)
        {
            throw new ArgumentNullException("Entitatea nu poate fi null.");
        }

        Validator.Validate(entity);

        if (Entities.ContainsKey(entity.id))
        {
            return entity;
        }

        Entities[entity.id] = entity;
        return default(E);
    }

    public E Delete(ID id)
    {
        if (Entities.ContainsKey(id))
        {
            var entity = Entities[id];
            Entities.Remove(id);
            return entity;
        }

        return default(E);
    }

    public E Update(E entity)
    {
        if (entity == null)
        {
            throw new ArgumentNullException("Entitatea nu poate fi null.");
        }

        Validator.Validate(entity);

        if (!Entities.ContainsKey(entity.id))
        {
            return default(E);
        }
        Entities[entity.id] = entity;
        return default(E);
    }

    public E FindOne(ID id)
    {
        Entities.TryGetValue(id, out var entity);
        return entity;
    }
}