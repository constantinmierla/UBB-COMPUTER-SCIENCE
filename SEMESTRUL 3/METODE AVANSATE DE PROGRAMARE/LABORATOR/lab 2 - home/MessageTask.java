import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class MessageTask extends Task {
    private String message;
    private String from;
    private String to;
    private LocalDateTime date;
    private static final DateTimeFormatter dateFormatter=DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");

    public MessageTask(String id, String desc, String message, String from, String to, LocalDateTime date) {
        super(id, desc);
        this.message = message;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    @Override
    public void execute()
    {
        System.out.println(date.format(dateFormatter)+": "+message);
    }

    @Override
    public String toString() {
        return "id="+getId()+"| description="+getDescription()+"| message="+message+"| from="+from+"| to="+to+"| date="+date.format(dateFormatter);
    }
}
