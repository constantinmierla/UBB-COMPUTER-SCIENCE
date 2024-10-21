import java.util.List;
import java.util.ArrayList;
public class Main {
    public static void main(String[] args) {
        Movie m1 = new Movie("IT", 2018);
        HorrorMovie m2 = new HorrorMovie("IT2", 2020, 70);
        HorrorMovie m3 = new HorrorMovie("IT3", 2022, 90);
        ActionMovie m4 = new ActionMovie("Annabelle", 2010,true);

        List<Movie> M = new ArrayList<>();
        M.add(m1);
        M.add(m2);
        M.add(m3);
        M.add(m4);

        for(Movie u : M)
        {
            if(u instanceof ActionMovie)
            {
                System.out.println(u);
            }
        }

        FileSearchTest f = new FileSearchTest();
        f.searchForTest("input.txt");

        LongestWordFinder l = new LongestWordFinder();
        System.out.println(l.findLongestWord("words.txt"));

        RandomString r = new RandomString();
        r.generateRandomStrings("output.txt", 10);
    }
}