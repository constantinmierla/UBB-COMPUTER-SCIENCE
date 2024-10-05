import java.time.LocalDateTime;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        MessageTask[] tasks = new MessageTask[5];
        tasks[0] = new MessageTask("1", "mail", "cv", "arthur", "employer", LocalDateTime.now());
        tasks[1] = new MessageTask("2", "mail", "cv", "arthuro", "employer", LocalDateTime.now());
        tasks[2] = new MessageTask("3", "mail", "cv", "arthurito", "employer", LocalDateTime.now());
        tasks[3] = new MessageTask("4", "mail", "cv", "arthurel", "employer", LocalDateTime.now());
        tasks[4] = new MessageTask("5", "mail", "cv", "arthurica", "employer", LocalDateTime.now());

        for (MessageTask task : tasks) {
            System.out.println(task);
        }
    }
}