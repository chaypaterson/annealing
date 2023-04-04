annealing
=========

This project should demonstrate the use of simulated annealing to find the
minimum of the function

    energy(x) := -2 * (x^(1/x))

It should return "xmin", the value of x that minimises energy(x), to within a
chosen precision.

In theory, xmin should be Euler's number, 2.718...

Compiling
---------

This program should consist of a single header file, annealing.h, and a single
ANSI C program, annealing.c. It should compile by running

    cc annealing.c -o anneal -lm

in a terminal, where "cc" is your choice of either GCC or Clang. (On Linux with
GCC, I needed to pass -lm. This might vary for you.)

Running
-------

The program should accept one argument, and run with

    ./anneal [precision]

It should print:

    [xmin] [estimated precision]

followed by a newline.

For example:

    ./anneal 1e-4

should return

    2.7183(...) 0.0001

Algorithm
---------

The basic algorithm is detailed in pseudocode
[here](https://en.wikipedia.org/wiki/Simulated_annealing#Pseudocode). The
overall idea is to try various "neighbouring" values of x, and accept them if
they are smaller. To avoid becoming trapped in local minima, there is some
random probability that we accept a higher value of x. This probability gets
stricter and stricter as the temperature T decreases.

There are several parts of the pseudocode algorithm on Wikipedia that are left unspecified. I will make the following suggestions. (I might be wrong.)

    1. What "neighbours" of x should we try each step?
        I suggest choosing the next neighbour of x from a uniform distribution
        between [x-w, x+w]. w could be 
            w = x * (precision + sqrt(T)) / (x + sqrt(T));
        This way, the "hops" to nearest neighbours start out large and gradually
        approach "precision".
    2. For the acceptance probability, I would choose

    double prob_accept(double x_new, double x_best, double T) {
        if (x_new < x_best) return 1.0;
        else return exp((x_best - x_new) / T);
    }

    or something equivalent if you can think of a shorter way of doing it.
