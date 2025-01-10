namespace project;

class Husky : Dog
{
    public int Speed { get; set; }

    public Husky(string name, int age, int speed) : base(name, age)
    {
        Speed = speed;
    }

    public void Run()
    {
        Console.WriteLine($"{Name} is running at a speed of {Speed} km/h...");
    }
}