import java.io.*;
public class LongestWordFinder {
    public String findLongestWord(String filename){
        String longestword = "";

        try(BufferedReader br = new BufferedReader(new FileReader(filename))){
            String word;
            while ((word = br.readLine()) != null){
                if(word.length() > longestword.length())
                {
                    longestword = word;
                }
            }
        } catch (IOException e){
            e.printStackTrace();
        }

        return longestword;
    }
}
