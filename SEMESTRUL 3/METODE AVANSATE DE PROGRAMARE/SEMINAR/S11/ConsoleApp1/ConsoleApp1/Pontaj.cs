namespace ConsoleApp1;

public class Pontaj
{
    public Angajat Angajat { get; set; }
    public Sarcina Sarcina { get; set; }
    public DateTime Data { get; set; }

    public override string ToString()
    {
        return $"Angajat: {Angajat.id}, Sarcina: {Sarcina.id}, Data: {Data.ToShortDateString()}";
    }
}