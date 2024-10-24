public class StrategyTaskRunner implements TaskRunner {
    private final Container container;

    public StrategyTaskRunner(Strategy s) {
        this.container = TaskContainerFactory.getInstance().createContainer(s);
    }

    @Override
    public void executeOneTask() {
        Task t = this.container.remove();
        t.execute();
    }

    @Override
    public void executeAll() {
        while (hasTask())
            executeOneTask();
    }

    @Override
    public void addTask(Task t) {
        this.container.add(t);
    }

    @Override
    public boolean hasTask() {
        return !container.isEmpty();
    }
}
