package HistogramWariant1;

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
        try {
            obraz.updateHistogram(symbol);
            obraz.printHistogram(threadNumber, symbol);

            if (Thread.interrupted()) {
                throw new InterruptedException();
            }

        } catch (InterruptedException e) {
            System.out.println("Wątek został przerwany: " + e.getMessage());
        }
    }
}