import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class MessageTask extends Task{
    private String message;
    private String from;
    private String to;
    private LocalDateTime date;

    private static final DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");

    @Override
    public String toString() {
        return "id=" + getId() + " | " + "description=" + getDescription() + " | message=" + message + " | from=" +
                from + " | to=" + to + " | date=" + formatter.format(date);
    }

    public MessageTask(String description, String id, String message, String from, String to, LocalDateTime date) {
        super(description, id);
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
    public void execute() {
        System.out.println(date.format(formatter)+": "+message);
    }
}
