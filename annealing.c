#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "annealing.h"

double energy(double x) {
    double power = log(x);
    power /= x;
    return -2 * exp(power);
}

double uniform(double x, double w) {
    double rand_num = (double) rand() / RAND_MAX; 
    double scaled_num = (rand_num * 2 - 1) * w; 
    return x + scaled_num;
}

double annealing_min(double (*obj_fun)(double),
                     double x_initial_guess,
                     double precision)  {
    const double Tmin = 1e-8; // Minimal temperature
    const double delta = 0.98; // The rate of temperature drop
    double t = 100;             // Initial temperature 

    srand((unsigned)time(NULL));

    double x = x_initial_guess;
    double best_x = x ;
    double best_y = obj_fun(best_x);
    double delta_x = 0;

    // Main loop:
    while ((t > Tmin) || (delta_x * delta_x > precision * precision)) {
        // sampling x method 1
        double w = x + precision;
        double x_new = uniform(x, w);

        double y_new = obj_fun(x_new);

        double delta_x = x_new - best_x;
        double delta_y = y_new - best_y;

        if (delta_y < 0) {
            x = x_new;
            best_x = x;
            best_y = y_new;
        } else {
            double p = exp(-delta_y / t);
            double rd = rand() / (RAND_MAX + 1.0);
            if (rd < p) {
                x = x_new;
                best_x = x;
                best_y = y_new;
            }
        }
        t *= delta;
        printf("%g %g, %g %g, %g\n", x_new, y_new, best_x, best_y, delta_y);
    }
    return best_x;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("This program should be invoked like this:\n");
        printf("    ./anneal [precision]\n");
        printf("where [precision] is your chosen precision for the answer.\n");
        return 1;
    } else { 
        double x_guess = 100.0; // your choice
        double precision = atof(argv[1]); // replace me
        printf("Minimising objective function... \n ");
        double x_min = annealing_min(energy, x_guess, precision);
        printf("%g %g\n", x_min, precision);
        printf("Done\n");
    }

    return 0;
}

