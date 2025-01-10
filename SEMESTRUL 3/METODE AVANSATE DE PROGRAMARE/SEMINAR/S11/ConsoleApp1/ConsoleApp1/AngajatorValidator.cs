namespace ConsoleApp1;

public class AngajatValidator : IValidator<Angajat>
{
    public void Validate(Angajat angajat)
    {
        if (angajat == null)
        {
            throw new ValidationException("Angajatul nu poate fi null.");
        }

        if (string.IsNullOrWhiteSpace(angajat.id))
        {
            throw new ValidationException("ID-ul angajatului nu poate fi gol.");
        }

        if (string.IsNullOrWhiteSpace(angajat.Nume))
        {
            throw new ValidationException("Numele angajatului nu poate fi gol.");
        }

        if (angajat.VenitPeOra <= 0)
        {
            throw new ValidationException("Venitul pe oră trebuie să fie pozitiv.");
        }

        if (!Enum.IsDefined(typeof(Nivel), angajat.Nivel))
        {
            throw new ValidationException("Nivelul angajatului este invalid.");
        }
    }
}