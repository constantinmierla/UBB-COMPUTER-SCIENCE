public class TaskContainerFactory implements Factory {
    private static TaskContainerFactory instance = null;

    private TaskContainerFactory() {}
    public static TaskContainerFactory getInstance() {
        if (instance == null) {
            instance = new TaskContainerFactory();
        }
        return instance;
    }

    @Override
    public Container createContainer(Strategy s) {
        return switch (s) {
            case LIFO -> new StackContainer();
            case FIFO -> new QueueContainer();
        };
    }
}
