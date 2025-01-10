namespace project;

class Labrador : Dog
{
    public string Color { get; set; }

    public Labrador(string name, int age, string color) : base(name, age)
    {
        Color = color;
    }
}