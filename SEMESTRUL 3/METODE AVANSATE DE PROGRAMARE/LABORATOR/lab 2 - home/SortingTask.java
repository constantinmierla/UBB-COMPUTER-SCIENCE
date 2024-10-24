import java.util.Arrays;

public class SortingTask extends Task{
    private int[] numere;
    private Sorter sorter;

    public SortingTask(String id, String descr, int[] numere, SortingStrategy strategy) {
        super(id, descr);
        this.numere = numere;
        sorter = SortingFactory.getInstance().createSorter(strategy);
    }

    @Override
    public void execute() {
        sorter.sort(this.numere);
        System.out.println("Numere sortate: " + Arrays.toString(this.numere));
    }
}
