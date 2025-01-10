namespace ConsoleApp1;

public interface IValidator<E>
{
    void Validate(E entity);
}

public class ValidationException : Exception
{
    public ValidationException(string message) : base(message) { }
}
