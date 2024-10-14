public class QueueContainer extends AbstractTaskContainer{
    @Override
    public Task remove() {
        if(tasks.isEmpty()) {
            return null;
        }
        return tasks.removeFirst();
    }
}
