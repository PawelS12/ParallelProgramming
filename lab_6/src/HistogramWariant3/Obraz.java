package HistogramWariant3;
import java.util.Random;

class Obraz {

    private int sizeN;
    private int sizeM;
    private char[][] tab;
    private char[] tabSymb;
    private int[] histogram;

    public Obraz(int n, int m) {
        this.sizeN = n;
        this.sizeM = m;
        tab = new char[n][m];
        tabSymb = new char[94];
        histogram = new int[94];

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
        }
    }

    public int[] calculateLocalHistogram(int startRow, int endRow) {
        int[] localHistogram = new int[94];
        for (int i = startRow; i <= endRow; i++) {
            for (int j = 0; j < sizeM; j++) {
                char currentSymbol = tab[i][j];
                int symbolIndex = currentSymbol - 33;
                localHistogram[symbolIndex]++;
            }
        }
        return localHistogram;
    }

    public synchronized void mergeLocalHistogram(int[] localHistogram) {
        for (int i = 0; i < 94; i++) {
            histogram[i] += localHistogram[i];
        }
    }

    public void printEntireHistogram() {
        for (int i = 0; i < 94; i++) {
            System.out.print(tabSymb[i] + " " + histogram[i] + "\n");
        }
    }
}