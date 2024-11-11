package HistogramWariant1;
import java.util.Scanner;

class HistogramTest {

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        System.out.println("Set image size: n (rows), m (columns)");
        int n = scanner.nextInt();
        int m = scanner.nextInt();

        Obraz obraz1 = new Obraz(n, m);
        // obraz1.printEntireHistogram();

        HistogramThread[] threads = new HistogramThread[94];
        for (int i = 0; i < 94; i++) {
            threads[i] = new HistogramThread(i + 1, (char)(i + 33), obraz1); // od 33 - widoczne znaki
            threads[i].start();
        }

        for (int i = 0; i < 94; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        scanner.close();
    }
}