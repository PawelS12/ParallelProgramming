package JavaForkJoin;
import java.util.concurrent.RecursiveTask;

public class DivideTask extends RecursiveTask<int[]> {

    private static final int THRESHOLD = 10; // Minimalna wielkość podziału
    private int[] arrayToDivide;

    public DivideTask(int[] arrayToDivide) {
        this.arrayToDivide = arrayToDivide;
    }

    @Override
    protected int[] compute() {
        if (arrayToDivide.length <= THRESHOLD) {
            // Sortowanie sekwencyjne dla małych tablic
            return sequentialSort(arrayToDivide);
        } else {
            // Podziel tablicę na pół
            int mid = arrayToDivide.length / 2;

            int[] leftPart = new int[mid];
            int[] rightPart = new int[arrayToDivide.length - mid];

            System.arraycopy(arrayToDivide, 0, leftPart, 0, mid);
            System.arraycopy(arrayToDivide, mid, rightPart, 0, rightPart.length);

            // Utwórz nowe zadania
            DivideTask task1 = new DivideTask(leftPart);
            DivideTask task2 = new DivideTask(rightPart);

            // Uruchom zadania równolegle
            task1.fork();
            task2.fork();

            // Czekaj na wyniki i scal
            int[] sortedLeft = task1.join();
            int[] sortedRight = task2.join();

            int[] result = new int[arrayToDivide.length];
            scal_tab(sortedLeft, sortedRight, result);

            return result;
        }
    }

    private int[] sequentialSort(int[] array) {
        // Proste sortowanie np. przez wstawianie
        java.util.Arrays.sort(array);
        return array;
    }

    private void scal_tab(int[] tab1, int[] tab2, int[] scal_tab) {
        int i = 0, j = 0, k = 0;

        while ((i < tab1.length) && (j < tab2.length)) {
            if (tab1[i] < tab2[j]) {
                scal_tab[k++] = tab1[i++];
            } else {
                scal_tab[k++] = tab2[j++];
            }
        }

        while (i < tab1.length) {
            scal_tab[k++] = tab1[i++];
        }

        while (j < tab2.length) {
            scal_tab[k++] = tab2[j++];
        }
    }
}
