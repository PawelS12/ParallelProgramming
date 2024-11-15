package HistogramWariant3;

public class HistogramThread implements Runnable {
    private int threadNumber;
    private int startRow;
    private int endRow;
    private Obraz obraz;

    public HistogramThread(int threadNumber, int startRow, int endRow, Obraz obraz) {
        this.threadNumber = threadNumber;
        this.startRow = startRow;
        this.endRow = endRow;
        this.obraz = obraz;
    }

    @Override
    public void run() {
        int[] localHistogram = obraz.calculateLocalHistogram(startRow, endRow);
        obraz.mergeLocalHistogram(localHistogram);
    }
}