public class SortingFactory {
    private static SortingFactory instance = null;

    private SortingFactory() {}

    public static SortingFactory getInstance() {
        if (instance == null) {
            instance = new SortingFactory();
        }
        return instance;
    }

    public Sorter createSorter(SortingStrategy strategy) {
        if(strategy.equals(SortingStrategy.BubbleSort))
            return new BubbleSort();
        else
            return new MergeSort();
    }
}
