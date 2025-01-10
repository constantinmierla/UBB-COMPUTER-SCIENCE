// See https://aka.ms/new-console-template for more information
namespace ConsoleApp1;
class Program
{
    static void Main(string[] args)
    {
        var validator = new AngajatValidator();
        //var repo = new AngajatFileRepository(validator, "angajati.txt");

        // Add a new employee
        var angajat = new Angajat
        {
            id = "A1",
            Nume = "Ion Popescu",
            VenitPeOra = 45,
            Nivel = Nivel.Medium
        };

        repo.Save(angajat);

        // Display all employees
        Console.WriteLine("Lista angajati:");
        foreach (var a in repo.FindAll())
        {
            Console.WriteLine(a);
        }
    }
}