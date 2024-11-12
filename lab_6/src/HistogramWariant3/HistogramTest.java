package HistogramWariant3;
import java.util.Scanner;

public class HistogramTest {

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        System.out.println("Set image size: n (rows), m (columns)");
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        System.out.println("Set number of threads:");
        int numThreads = scanner.nextInt();

        Obraz obraz1 = new Obraz(n, m);

        int rowsPerThread = n / numThreads;
        int extraRows = n % numThreads;
        Thread[] threads = new Thread[numThreads];

        for (int i = 0; i < numThreads; i++) {
            int startRow = i * rowsPerThread;
            int endRow = (i + 1) * rowsPerThread - 1;

            if (i == numThreads - 1) {
                endRow += extraRows;
            }

            threads[i] = new Thread(new HistogramThread(i + 1, startRow, endRow, obraz1));
            threads[i].start();
        }

        for (int i = 0; i < numThreads; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        obraz1.printEntireHistogram();

        scanner.close();
    }
}