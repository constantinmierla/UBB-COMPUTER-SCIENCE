import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class DelayTaskRunner extends AbstractTaskRunner{
    public DelayTaskRunner(TaskRunner taskRunner) {
        super(taskRunner);
    }

    private static final DateTimeFormatter formatter = DateTimeFormatter.ofPattern("HH:mm");

    @Override
    public void executeOneTask(){
        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        super.executeOneTask();
    }
}
