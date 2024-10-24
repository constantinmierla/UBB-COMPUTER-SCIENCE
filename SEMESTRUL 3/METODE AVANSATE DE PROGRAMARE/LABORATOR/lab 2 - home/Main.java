import java.time.LocalDateTime;

public class Main {
    public static MessageTask[] getMessages(){
        MessageTask[] tasks = new MessageTask[5];
        tasks[0]=new MessageTask("0001", "feedback 1", "read this", "Gigi","Ana", LocalDateTime.now());
        tasks[1] = new MessageTask("0002", "feedback 2", "please check", "Ana", "Maria", LocalDateTime.now());
        tasks[2] = new MessageTask("0003", "feedback 3", "review the details", "Maria", "Ioana", LocalDateTime.now());
        tasks[3] = new MessageTask("0004", "feedback 4", "see attached document", "Ioana", "Gigi", LocalDateTime.now());
        tasks[4] = new MessageTask("0005", "feedback 5", "provide your input", "Gigi", "Ana", LocalDateTime.now());

        return tasks;
    }

    public static void writeMessageTasks(MessageTask[] tasks) {
        for (MessageTask task : tasks) {
            System.out.println(task);
        }
    }

    public static void main(String[] args) {
        MessageTask[] tasks = Main.getMessages();

        // subpct 4
        Main.writeMessageTasks(tasks);

        /* strategy task runner */
        System.out.println("Strategy: ");
        StrategyTaskRunner taskRunner=new StrategyTaskRunner(Strategy.valueOf(args[0]));
        for (MessageTask task: tasks)
        {
            taskRunner.addTask(task);
        }
        taskRunner.executeAll();

        // decoram cu PrinterTaskRunner
        System.out.println("Printer: ");
        TaskRunner printerTaskRunner = new PrinterTaskRunner(taskRunner);
        for(MessageTask task: tasks) {
            printerTaskRunner.addTask(task);
        }
        printerTaskRunner.executeAll();

        // decoram cu DelayTaskRunner
        System.out.println("Delay: ");
        TaskRunner delayTaskRunner = new DelayTaskRunner(printerTaskRunner);
        for(MessageTask task: tasks) {
            delayTaskRunner.addTask(task);
        }
        delayTaskRunner.executeAll();
    }
}