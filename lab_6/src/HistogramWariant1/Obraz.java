package HistogramWariant1;
import java.util.Random;

class Obraz {

    private int sizeN;
    private int sizeM;
    private char[][] tab;
    private char[] tabSymb;
    private int[] histogram;
    private int[] hist_parallel;

    public Obraz(int n, int m) {
        this.sizeN = n;
        this.sizeM = m;
        tab = new char[n][m];
        tabSymb = new char[94];
        histogram = new int[94];
        hist_parallel = new int[94];

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
            hist_parallel[i] = 0;
        }
    }

    public void calculateHistogram(){
        for(int i=0;i<sizeN;i++) {
            for(int j=0;j<sizeM;j++) {
                for(int k=0;k<94;k++) {
                    if(tab[i][j] == tabSymb[k]) histogram[k]++;

                }
            }
        }
    }

    public void updateHistogramParallel(char symbol) {
        int symbolIndex = symbol - 33;
        for (int i = 0; i < sizeN; i++) {
            for (int j = 0; j < sizeM; j++) {
                if (tab[i][j] == symbol) {
                    hist_parallel[symbolIndex]++;
                }
            }
        }
    }

    public synchronized void printHistogram(int threadNumber, char symbol) {
        int symbolIndex = symbol - 33;
        int count = hist_parallel[symbolIndex];
        System.out.print("Thread " + threadNumber + ": " + symbol + " ");
        for (int i = 0; i < count; i++) {
            System.out.print("=");
        }
        System.out.println();
    }

    public void printEntireHistogram() {
        for (int i = 0; i < 94; i++) {
            System.out.print(tabSymb[i] + " " + histogram[i] + "\n");
        }
    }

    public void printEntireParallelHistogram() {
        for (int i = 0; i < 94; i++) {
            System.out.print(tabSymb[i] + " " + hist_parallel[i] + "\n");
        }
    }

    public void verifyHistograms() {
        boolean isEqual = true;
        for (int i = 0; i < 94; i++) {
            if (histogram[i] != hist_parallel[i]) {
                System.out.println("Mismatch found for symbol " + tabSymb[i] + ": sekwencyjnie = " + histogram[i] + ", rownolegle = " + hist_parallel[i]);
                isEqual = false;
            }
        }
        if (isEqual) {
            System.out.println("Histogramy pasuja do siebie");
        } else {
            System.out.println("Histogramy nie pasuja.");
        }
    }
}