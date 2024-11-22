package HistogramWariant2;
import java.util.Random;

class Obraz {

    private int sizeN;
    private int sizeM;
    private char[][] tab;
    private char[] tabSymb;
    private int[] histogram;
    private int[] histParallel;

    public Obraz(int n, int m) {
        this.sizeN = n;
        this.sizeM = m;
        tab = new char[n][m];
        tabSymb = new char[94];
        histogram = new int[94];
        histParallel = new int[94];

        final Random random = new Random();

        for (int k = 0; k < 94; k++) {
            tabSymb[k] = (char) (k + 33);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                tab[i][j] = tabSymb[random.nextInt(94)];
                System.out.print(tab[i][j] + " ");
            }
            System.out.print("\n");
        }
        System.out.print("\n\n");

        clearHistogram();
    }

    public synchronized void clearHistogram() {
        for (int i = 0; i < 94; i++) {
            histogram[i] = 0;
            histParallel[i] = 0;
        }
    }

    public void calculateHistogram() {
        for (int i = 0; i < sizeN; i++) {
            for (int j = 0; j < sizeM; j++) {
                int symbolIndex = tab[i][j] - 33;
                histogram[symbolIndex]++;
            }
        }
    }

    public void updateHistogramParallel(char startSymbol, char endSymbol) {
        for (int i = 0; i < sizeN; i++) {
            for (int j = 0; j < sizeM; j++) {
                char currentSymbol = tab[i][j];
                if (currentSymbol >= startSymbol && currentSymbol <= endSymbol) {
                    int symbolIndex = currentSymbol - 33;
                    histParallel[symbolIndex]++;
                }
            }
        }
    }

    public synchronized void printHistogram(int threadNumber, char symbol) {
        int symbolIndex = symbol - 33;
        int count = histParallel[symbolIndex];
        System.out.print("Thread " + threadNumber + ": " + symbol + " ");
        for (int i = 0; i < count; i++) {
            System.out.print("=");
        }
        System.out.println();
    }

    public void printEntireHistogram() {
        System.out.println("Sequential Histogram:");
        for (int i = 0; i < 94; i++) {
            System.out.print(tabSymb[i] + " " + histogram[i] + "\n");
        }
    }

    public void printEntireParallelHistogram() {
        System.out.println("Parallel Histogram:");
        for (int i = 0; i < 94; i++) {
            System.out.print(tabSymb[i] + " " + histParallel[i] + "\n");
        }
    }

    public void verifyHistograms() {
        boolean isEqual = true;
        for (int i = 0; i < 94; i++) {
            if (histogram[i] != histParallel[i]) {
                System.out.println("Mismatch found for symbol " + tabSymb[i] + ": sequentially = " + histogram[i] + ", parallelly = " + histParallel[i]);
                isEqual = false;
            }
        }
        if (isEqual) {
            System.out.println("The histograms match.");
        } else {
            System.out.println("The histograms do not match.");
        }
    }
}