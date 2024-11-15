package HistogramWariant2;

public class HistogramThread implements Runnable {
    private int threadNumber;
    private char startChar;
    private char endChar;
    private Obraz obraz;

    public HistogramThread(int threadNumber, char startChar, char endChar, Obraz obraz) {
        this.threadNumber = threadNumber;
        this.startChar = startChar;
        this.endChar = endChar;
        this.obraz = obraz;
    }

    @Override
    public void run() {
        obraz.updateHistogramParallel(startChar, endChar);

        for (char c = startChar; c <= endChar; c++) {
            obraz.printHistogram(threadNumber, c);
        }
    }
}
