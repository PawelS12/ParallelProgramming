package JavaForkJoin;
import java.util.concurrent.ForkJoinPool;

public class SortExecutor {

    public static void main(String[] args) {
        int[] arrayToSort = {
                89, 45, 68, 90, 29, 34, 17, 23, 76, 11,
                55, 38, 92, 81, 47, 66, 73, 58, 99, 10,
                41, 15, 84, 62, 31, 78, 5, 12, 48, 9,
                100, 3, 27, 50, 71, 25, 40, 88, 22, 64,
                36, 60, 19, 70, 83, 46, 95, 1, 67, 13,
                28, 4, 54, 79, 42, 94, 33, 80, 37, 18,
                96, 8, 26, 59, 52, 75, 87, 2, 16, 93,
                35, 72, 6, 63, 43, 82, 7, 77, 53, 20,
                85, 30, 44, 97, 21, 56, 74, 49, 24, 61,
                65, 32, 39, 86, 14, 98, 51, 57, 91
        };

        // Utwórz pulę ForkJoin
        ForkJoinPool pool = new ForkJoinPool();

        // Rozpocznij zadanie sortowania
        DivideTask mainTask = new DivideTask(arrayToSort);
        int[] sortedArray = pool.invoke(mainTask);

        // Wyświetl posortowaną tablicę
        System.out.println("Sorted array: ");
        for (int num : sortedArray) {
            System.out.print(num + " ");
        }

        pool.shutdown();
    }
}
