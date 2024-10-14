public class BubbleSort implements Sorter{
    @Override
    public void sort(int[] numere) {
        boolean sortat = false;

        while(!sortat){
            sortat = true;

            for (int i = 0; i < numere.length - 1; i++) {
                if (numere[i] > numere[i + 1]) {
                    sortat = false;
                    int aux = numere[i];
                    numere[i] = numere[i + 1];
                    numere[i + 1] = aux;
                }
            }
        }
    }
}
