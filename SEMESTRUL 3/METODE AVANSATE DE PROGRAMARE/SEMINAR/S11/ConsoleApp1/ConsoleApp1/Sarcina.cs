namespace ConsoleApp1;

public class Sarcina : Entity<string>
{
    public Dificultate Dificultate { get; set; }
    public int NrOreEstimate { get; set; }

    public override string ToString()
    {
        return $"ID: {id}, Dificultate: {Dificultate}, NrOre: {NrOreEstimate}";
    }
}
public enum Dificultate
{
    Usoara,
    Medie,
    Grea
}