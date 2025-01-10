using System;
using System.Collections.Generic;
namespace project;
class Program
{

    static void Main(string[] args)
    {
        List<Dog> dogs = new List<Dog>
        {
            new Husky("Husky1", 3, 20),
            new Husky("Husky2", 5, 25),
            new Labrador("Labrador1", 2, "White"),
            new Labrador("Labrador2", 4, "Beige"),
            new Dog("Dog1", 6)
        };

        Console.WriteLine("All dogs eating:");
        foreach (var dog in dogs)
        {
            dog.Eat();
        }

        Console.WriteLine("\nOnly Husky dogs:");
        foreach (var dog in dogs)
        {
            if (dog is Husky husky)
            {
                Console.WriteLine($"Husky: {husky.Name}, Age: {husky.Age}, Speed: {husky.Speed}");
            }
        }

        Dictionary<int, string> addresses = new Dictionary<int, string>
        {
            {1, "Str. Progresului"},
            {2, "Str. Libertatii"},
            {3, "Str. Independentei"}
        };

        Console.WriteLine("\nAddresses:");
        foreach (var entry in addresses)
        {
            Console.WriteLine($"{entry.Key} -> {entry.Value}");
        }
    }
}
