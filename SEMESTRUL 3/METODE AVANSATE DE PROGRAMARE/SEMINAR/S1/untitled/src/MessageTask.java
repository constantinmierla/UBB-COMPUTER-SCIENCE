import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class MessageTask extends Task{
    private String message;
    private String from;
    private String to;
    private LocalDateTime date;

    private static final DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");


    public MessageTask(String id, String description, String message, String from, String to, LocalDateTime date) {
        super(id, description);
        this.message = message;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public String getFrom() {
        return from;
    }

    public void setFrom(String from) {
        this.from = from;
    }

    public String getTo() {
        return to;
    }

    public void setTo(String to) {
        this.to = to;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    @Override
    public String toString() {
        return "MessageTask{" +
                "message='" + message + '\'' +
                ", from='" + from + '\'' +
                ", to='" + to + '\'' +
                ", date=" + date +
                '}';
    }

    @Override
    public void execute() {
        System.out.println(date.format(formatter) + ": "+ message);
    }
}
