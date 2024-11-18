package JavaForkJoin;
import java.util.concurrent.ForkJoinPool;

public class SortExecutor {
    public static void main(String[] args) {
        int[] arrayToSort = {
                89, 45, 68, 90, 29, 34, 17, 23, 76, 11,
                55, 38, 92, 81, 47, 66, 73, 58, 99, 10,
                41, 15, 84, 62, 31, 78, 5, 12, 48, 9
        };

        ForkJoinPool pool = new ForkJoinPool();

        DivideTask mainTask = new DivideTask(arrayToSort);
        int[] sortedArray = pool.invoke(mainTask);

        System.out.println("Sorted array: ");
        for (int num : sortedArray) {
            System.out.print(num + " ");
        }

        pool.shutdown();
    }
}