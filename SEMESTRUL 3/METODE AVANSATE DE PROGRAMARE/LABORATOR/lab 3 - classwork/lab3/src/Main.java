import java.util.ArrayList;
import java.util.List;


public static void main(String[] args) {


        Circle c1 = new Circle(5);
        Circle c2 = new Circle(3);
        Circle c3 = new Circle(4);

        List<Circle> list = new ArrayList<>();
        list.add(c1);
        list.add(c2);
        list.add(c3);

        Circle circle = ElementUtils.lastEntry(list);

        System.out.println(circle);

        List<String>words= new ArrayList<>();
        words.add("java");
        words.add("c++");
        words.add("python");

        String lastWord = ElementUtils.lastEntry(words);
        System.out.println(lastWord);
    }