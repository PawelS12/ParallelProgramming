class HistogramThread extends Thread {

    private char symbol;
    private Obraz obraz;
    private int threadNumber;

    public HistogramThread(int threadNumber, char symbol, Obraz obraz) {
        this.threadNumber = threadNumber;
        this.symbol = symbol;
        this.obraz = obraz;
    }

    @Override
    public void run() {
        obraz.update_histogram(symbol);
        obraz.print_histogram(threadNumber, symbol);
    }
}