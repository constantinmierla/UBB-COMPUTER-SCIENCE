import java.util.*;
import java.util.stream.Collectors;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        List<String> cuvinte = Arrays.asList("Taxi", "driver", "coco", "costi");
        List<String> majuscule = cuvinte.stream()
                .map(String::toUpperCase)
                .collect(Collectors.toList());
        System.out.println(majuscule);

        System.out.println("age > 10");
        List<Dog> dogs = new ArrayList<>();
        dogs.add(new Dog("Rex", 17));
        dogs.add(new Dog("Tex", 6));
        dogs.add(new Dog("Dex", 9));
        dogs.add(new Dog("Bex", 11));
        dogs.add(new Dog("Sam", 11));

        dogs.stream()
                .filter(e -> e.getAge()> 10)
                .forEach(System.out::println);

        System.out.println("age sorted dsc");
        List<Dog> sorted_dogs = dogs.stream()
                .sorted(Comparator.comparingInt(Dog::getAge).reversed())
                .collect(Collectors.toList());
        sorted_dogs.forEach(System.out::println);

        System.out.println("Sam");
        dogs.stream()
                .filter(e -> "Sam".equals(e.getName()))
                .findAny()
                .ifPresent(System.out::println);

        System.out.println("All dogs' name");
        dogs.stream()
                .map(Dog::getName)
                .forEach(System.out::println);

        System.out.println("perfect square: ");
        List<Integer> numbers = Arrays.asList(1,2,3,4,5);
        List<Integer> square = numbers.stream()
                .map(e -> e*e)
                .collect(Collectors.toList());
        System.out.println(square);

        System.out.println("Mall:");

        List<Mall> malls = new ArrayList<>();
        malls.add(new Mall("iulis","radu",2010, 50000.0));
        malls.add(new Mall("ciulis","raul",2000, 250.0));
        malls.add(new Mall("diulis","paul",2016, 370.0));
        malls.add(new Mall("ziulis","saul",2011, 50000.0));

        malls.forEach(e -> e.setProfit(e.getProfit()*3));
        Mall maxim = malls.stream()
                .max(Comparator.comparingDouble(Mall::getProfit))
                .orElse(null);
        System.out.println(maxim);

    }
}
