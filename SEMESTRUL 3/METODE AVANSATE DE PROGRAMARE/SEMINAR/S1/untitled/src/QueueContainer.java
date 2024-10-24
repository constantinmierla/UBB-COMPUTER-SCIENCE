import java.util.ArrayList;
import java.util.List;

public class QueueContainer implements Container{
    private List<Task> tasks = new ArrayList<>();

    @Override
    public Task remove() {
        return null;
    }

    @Override
    public void add(Task task) {

    }

    @Override
    public int size() {
        return 0;
    }

    @Override
    public boolean isEmpty() {
        return false;
    }
}
