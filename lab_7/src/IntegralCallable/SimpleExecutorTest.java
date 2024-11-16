package IntegralCallable;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class SimpleExecutorTest {

    private static final int NTHREADS = 10;

    public static void main(String[] args) throws InterruptedException, ExecutionException {

        //------------------------------------------------------------------
        // Wersja sekwencyjna

        double xp = 0;
        double xk = Math.PI;
        double dx = 0.00001;

        CalkaCallable calka1 = new CalkaCallable(xp, xk, dx);
        calka1.computeIntegral();

        //------------------------------------------------------------------
        // Wersja równoległa

        ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);
        List<Future<Double>> results = new ArrayList<>();

        int tasks = 30;
        double subInterval = (xk - xp) / tasks;

        for (int i = 0; i < tasks; i++) {
            double subXp = xp + i * subInterval;
            double subXk = subXp + subInterval;

            CalkaCallable task = new CalkaCallable(subXp, subXk, dx);
            results.add(executor.submit(task));
        }
        executor.shutdown();

        double totalIntegral = 0;
        for (Future<Double> result : results) {
            totalIntegral += result.get();
        }

        System.out.println("Finished all threads");
        System.out.println("Total integral: " + totalIntegral);
    }
}