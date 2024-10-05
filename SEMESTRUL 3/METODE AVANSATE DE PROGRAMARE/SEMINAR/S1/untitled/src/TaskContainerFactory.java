public class TaskContainerFactory {
    //private constructor
    //public static TaskContainerFactory get_instance()
    public Container createContainer(Strategy strategy){
        switch(strategy){
            case FIFO:
                return new QueueContainer();
            case LIFO:
                return new StackContainer();
            default: return null;
        }
    }
}
