package HistogramWariant1;

class HistogramThread extends Thread {
    private int threadNumber;
    private char symbol;
    private Obraz obraz;

    public HistogramThread(int threadNumber, char symbol, Obraz obraz) {
        this.threadNumber = threadNumber;
        this.symbol = symbol;
        this.obraz = obraz;
    }

    @Override
    public void run() {
        obraz.updateHistogramParallel(symbol);
        obraz.printHistogram(threadNumber, symbol);
    }
}