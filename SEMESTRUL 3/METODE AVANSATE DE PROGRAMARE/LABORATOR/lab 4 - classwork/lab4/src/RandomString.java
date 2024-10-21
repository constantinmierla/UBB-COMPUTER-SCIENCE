import java.io.*;
import java.util.*;
public class RandomString {
    public void generateRandomStrings(String filename, int numberofRandoms){
        List<String> randomStrings = new ArrayList<>();
        for(int i = 0; i < numberofRandoms; i++)
        {
            double randomNum = Math.random();
            randomStrings.add(String.valueOf(randomNum));
        }

        try(BufferedWriter bw = new BufferedWriter(new FileWriter(filename))){
            for(String s : randomStrings){
                bw.write(s);
                bw.newLine();
            }
        } catch(IOException e) {
            e.printStackTrace();
        }
    }
}
