package JavaForkJoin;
import java.util.concurrent.ForkJoinPool;

public class SortExecutor {
    public static void main(String[] args) {
        int[] arrayToSort = { 89, 45, 68, 90, 29, 34, 17, 23, 76, 11 };

        System.out.println("Array to sort: ");
        for (int num : arrayToSort) {
            System.out.print(num + " ");
        }
        System.out.println();

        ForkJoinPool pool = new ForkJoinPool();

        DivideTask mainTask = new DivideTask(arrayToSort);
        int[] sortedArray = pool.invoke(mainTask);

        System.out.println("\nSorted array: ");
        for (int num : sortedArray) {
            System.out.print(num + " ");
        }

        pool.shutdown();
    }
}