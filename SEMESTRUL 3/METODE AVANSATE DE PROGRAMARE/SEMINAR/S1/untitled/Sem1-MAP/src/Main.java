import java.time.LocalDateTime;

public class Main {
    public static void main(String[] args) {
        MessageTask[] tasks = new MessageTask[5];
        tasks[0]=new MessageTask("mail", "1", "cv", "arthur", "employer", LocalDateTime.now());
        tasks[1]=new MessageTask("mail", "2", "resignation letter", "steffen", "employer", LocalDateTime.now());
        tasks[2]=new MessageTask("mail", "3", "cv", "steve", "employer", LocalDateTime.now());
        tasks[3]=new MessageTask("mail", "4", "cv", "mary", "employer", LocalDateTime.now());
        tasks[4]=new MessageTask("mail", "5", "cv", "margaret", "employer", LocalDateTime.now());

        for (MessageTask task : tasks) {
            System.out.println(task);
        }

        StrategyTaskRunner strategyTaskRunner=new StrategyTaskRunner(Strategy.valueOf(args[0]));
        for (MessageTask task : tasks) {
            strategyTaskRunner.addTask(task);
        }

        //strategyTaskRunner.executeAll();

        PrinterTaskRunner printerTaskRunner = new PrinterTaskRunner(strategyTaskRunner);
        //printerTaskRunner.executeAll();

        DelayTaskRunner delayTaskRunner = new DelayTaskRunner(new DelayTaskRunner(printerTaskRunner));
        delayTaskRunner.executeAll();

    }
}