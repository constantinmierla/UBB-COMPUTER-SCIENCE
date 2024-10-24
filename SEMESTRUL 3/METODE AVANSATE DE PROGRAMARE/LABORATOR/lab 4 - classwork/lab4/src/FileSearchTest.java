import java.io.*;
import java.util.*;

public class FileSearchTest {
    public void searchForTest(String filename){
        List<String> lines = new ArrayList<>();

        try(BufferedReader br = new BufferedReader(new FileReader(filename))){
            String line;
            while ((line = br.readLine()) != null){
                lines.add(line);
            }
        } catch(IOException e){
            e.printStackTrace();
        }

        for(String l : lines){
            if(l.contains("test")){
                System.out.println(l);
            }
        }
    }
}
