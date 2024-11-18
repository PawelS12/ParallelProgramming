package JavaForkJoin;
import java.util.concurrent.RecursiveTask;

public class DivideTask extends RecursiveTask<int[]> {

    private static final int THRESHOLD = 10;
    private int[] arrayToDivide;

    public DivideTask(int[] arrayToDivide) {
        this.arrayToDivide = arrayToDivide;
    }

    @Override
    protected int[] compute() {
        if (arrayToDivide.length <= THRESHOLD) {
            return sequentialSort(arrayToDivide);
        } else {
            int mid = arrayToDivide.length / 2;

            int[] leftPart = new int[mid];
            int[] rightPart = new int[arrayToDivide.length - mid];

            System.arraycopy(arrayToDivide, 0, leftPart, 0, mid);
            System.arraycopy(arrayToDivide, mid, rightPart, 0, rightPart.length);

            DivideTask task1 = new DivideTask(leftPart);
            DivideTask task2 = new DivideTask(rightPart);

            task1.fork();
            task2.fork();

            int[] sortedLeft = task1.join();
            int[] sortedRight = task2.join();

            int[] result = new int[arrayToDivide.length];
            scalTab(sortedLeft, sortedRight, result);

            return result;
        }
    }

    private int[] sequentialSort(int[] array) {
        java.util.Arrays.sort(array);
        return array;
    }

    private void scalTab(int[] tab1, int[] tab2, int[] scalTab) {
        int i = 0, j = 0, k = 0;

        while ((i < tab1.length) && (j < tab2.length)) {
            if (tab1[i] < tab2[j]) {
                scalTab[k++] = tab1[i++];
            } else {
                scalTab[k++] = tab2[j++];
            }
        }

        while (i < tab1.length) {
            scalTab[k++] = tab1[i++];
        }

        while (j < tab2.length) {
            scalTab[k++] = tab2[j++];
        }
    }
}
