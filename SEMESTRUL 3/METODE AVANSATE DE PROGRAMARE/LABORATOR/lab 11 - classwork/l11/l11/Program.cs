using System;

namespace lab11
{
    public class Person
    {
        protected int age;

        public void Greet()
        {
            Console.WriteLine("Hello");
        }

        public void SetAge(int n)
        {
            age = n;
        }
    }

    public class Student : Person
    {
        public void ShowAge()
        {
            Console.WriteLine($"My age is: {age} years old");
        }
    }

    public class Professor : Person
    {
        private string subject;

        public void Explain()
        {
            Console.WriteLine("Explanation begins");
        }

        public void SetSubject(string subject)
        {
            this.subject = subject;
        }
    }

    class Application
    {
        static void Main(string[] args)
        {
            Person person = new Person();
            Console.WriteLine("Person:");
            person.Greet();

            Student student = new Student();
            student.SetAge(21);
            Console.WriteLine("\nStudent:");
            student.Greet();
            student.ShowAge();

            Professor professor = new Professor();
            professor.SetAge(30);
            Console.WriteLine("\nProfessor:");
            professor.Explain();
            professor.Greet();

            Console.ReadKey();
        }
    }
}