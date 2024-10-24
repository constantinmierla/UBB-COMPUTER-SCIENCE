public class MergeSort implements Sorter{
    @Override
    public void sort(int[] numere) {
        mergeSort(numere, 0, numere.length - 1);
    }

    private void mergeSort(int[] v, int st, int dr) {
        if (st < dr) {
            int m = (st + dr) / 2;
            mergeSort(v, st, m);
            mergeSort(v, m + 1, dr);
            merge(v, st, dr);
        }
    }

    private void merge(int[] v, int st, int dr) {
        int m = (st + dr) / 2;
        int lgSt = m - st + 1;
        int lgDr = dr - m;

        int[] tempSt = new int[lgSt];
        int[] tempDr = new int[lgDr];

        for (int i = 0; i < lgSt; i++) {
            tempSt[i] = v[st + i];
        }
        for (int i = 0; i < lgDr; i++) {
            tempDr[i] = v[m + i + 1];
        }

        int i = 0, j = 0, k = st;
        while (i < lgSt && j < lgDr) {
            if (tempSt[i] < tempDr[j]) {
                v[k++] = tempSt[i];
                i++;
            }
            else {
                v[k++] = tempDr[j];
                j++;
            }
        }

        while (i < lgSt) {
            v[k++] = tempSt[i++];
        }
        while (j < lgDr) {
            v[k++] = tempDr[j++];
        }
    }
}
