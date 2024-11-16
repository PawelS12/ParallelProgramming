package IntegralCallable;

import java.util.concurrent.Callable;

public class CalkaCallable implements Callable<Double> {

    private double dx;
    private double xp;
    private double xk;
    private int N;

    public CalkaCallable(double xp, double xk, double dx) {
        this.xp = xp;
        this.xk = xk;
        this.N = (int) Math.ceil((xk - xp) / dx);
        this.dx = (xk - xp) / N;
        System.out.println("Creating an instance of CalkaSekwencyjna.IntegralCallable.CalkaCallable");
        System.out.println("xp = " + xp + ", xk = " + xk + ", N = " + N);
        System.out.println("dx requested = " + dx + ", dx final = " + this.dx);

    }

    private double getFunction(double x) {
        return Math.sin(x);
    }

    public double computeIntegral() {
        double integral = 0;
        int i;
        for(i = 0; i < N; i++){
            double x1 = xp + i * dx;
            double x2 = x1 + dx;
            integral += ((getFunction(x1) + getFunction(x2))/2.) * dx;
        }
        System.out.println("Partial integral: " + integral);
        System.out.println();

        return integral;
    }

    @Override
    public Double call() {
        double integral = 0;
        for (int i = 0; i < N; i++) {
            double x1 = xp + i * dx;
            double x2 = x1 + dx;
            integral += ((getFunction(x1) + getFunction(x2)) / 2.0) * dx;
        }
        System.out.println("Partial integral: " + integral);
        System.out.println();

        return integral;
    }
}
