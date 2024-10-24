public class TaskContainerFactory implements Factory{
    //private constructor
    //public static TaskContainerFactory get_instance()

    @Override
    public Container createContainer(Strategy strategy) {
        switch(strategy){
            case FIFO:
                return new QueueContainer();
            case LIFO:
                return new StackContainer();
            default: return null;
        }
    }
}
