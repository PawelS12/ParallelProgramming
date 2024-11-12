package HistogramWariant2;
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

        int range = 94 / numThreads;
        Thread[] threads = new Thread[numThreads];

        for (int i = 0; i < numThreads; i++) {
            char startChar = (char)(33 + i * range);
            char endChar;
            if (i == numThreads - 1) { // Jeśli jest to ostatni wątek to zakres jest do 126, by objąć wszystkie pozostałe znaki.
                endChar = (char)126;
            } else {
                endChar = (char)(33 + (i + 1) * range - 1); // ostatni znak w zakresie wątku
            }

            threads[i] = new Thread(new HistogramThread(i + 1, startChar, endChar, obraz1));
            threads[i].start();
        }

        for (int i = 0; i < numThreads; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        scanner.close();
    }
}