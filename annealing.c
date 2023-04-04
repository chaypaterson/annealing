#include <stdio.h>
#include "annealing.h"

double energy(double x) {
    double power = log(x);
    power /= x;
    return -2 * exp(power);
}

double prob_accept(double x_new, double x_best, double T) {
    if (x_new < x_best) return 1.0;
    else return exp((x_best - x_new) / T);
}

double annealing_min(double (*obj_fun)(double),
                     double x_initial_guess,
                     double precision) {
    double x_min = x_initial_guess;
    // The following block should be made into a loop:
    {
        double x_now = x_min;
        // We can call obj_fun like this:
        double energy_new = obj_fun(x_now);
        printf("%g\n", energy_new); // TEST PRINTF PLEASE REMOVE
        // ????
        // SIMULATED ANNEALING HAPPENS HERE!
        // Magic happens...
        // x_min is updated somehow...
        // ????
    }
    return x_min;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("This program should be invoked like this:\n");
        printf("    ./anneal [precision]\n");
        printf("where [precision] is your chosen precision for the answer.\n");
        return 1;
    } else { 
        double x_guess = 1.0; // replace me
        double precisn = 0.01; // replace me
        printf("Minimising objective function...\n");
        double x_min = annealing_min(energy, x_guess, precisn);
        printf("Done\n");
        printf("%g %g\n", x_min, precisn);
    }

    return 0;
}

