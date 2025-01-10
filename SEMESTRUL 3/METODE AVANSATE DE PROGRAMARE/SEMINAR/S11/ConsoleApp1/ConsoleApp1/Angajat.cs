namespace ConsoleApp1;

public class Angajat : Entity<string>
{
    public string Nume { get; set; }
    public double VenitPeOra { get; set; }
    public Nivel Nivel { get; set; }

    public override string ToString()
    {
        return $"{id}, {Nume}, {VenitPeOra}, {Nivel}";
    }
}

public enum Nivel
{
    Junior,
    Medium,
    Senior
}
