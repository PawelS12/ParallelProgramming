import java.util.Random;

class Obraz {

    private int sizeN;
    private int sizeM;
    private char[][] tab;
    private char[] tab_symb;
    private int[] histogram;

    public Obraz(int n, int m) {
        this.sizeN = n;
        this.sizeM = m;
        tab = new char[n][m];
        tab_symb = new char[94];
        histogram = new int[94];

        final Random random = new Random();

        for (int k = 0; k < 94; k++) {
            tab_symb[k] = (char) (k + 33);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                tab[i][j] = tab_symb[random.nextInt(94)];
                System.out.print(tab[i][j] + " ");
            }
            System.out.print("\n");
        }
        System.out.print("\n\n");

        clear_histogram();
    }

    public synchronized void clear_histogram() {
        for (int i = 0; i < 94; i++) histogram[i] = 0;
    }

    public synchronized void update_histogram(char symbol) {
        int symbolIndex = symbol - 33;
        for (int i = 0; i < sizeN; i++) {
            for (int j = 0; j < sizeM; j++) {
                if (tab[i][j] == symbol) {
                    histogram[symbolIndex]++;
                }
            }
        }
    }

    public synchronized void print_histogram(int threadNumber, char symbol) {
        int symbolIndex = symbol - 33;
        int count = histogram[symbolIndex];
        System.out.print("Wątek " + threadNumber + ": " + symbol + " ");
        for (int i = 0; i < count; i++) {
            System.out.print("=");
        }
        System.out.println();
    }
}