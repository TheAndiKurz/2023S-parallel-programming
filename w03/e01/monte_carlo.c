#include "../../tools/time/time.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef REDUCTION
#define VARIANT "Reduction"
#elif CRITICAL
#define VARIANT "Critical"
#else
#define VARIANT "Atomic"
#endif

double rand_double(unsigned* seed) {
    return (double)rand_r(seed) / (double)RAND_MAX;
}

double monte_carlo(size_t threads, size_t n) {
    size_t inside = 0;
#ifdef REDUCTION
#pragma omp parallel num_threads(threads) reduction(+ : inside)
#else
#pragma omp parallel num_threads(threads)
#endif
    {
        unsigned seed = time(NULL) + omp_get_thread_num();
#pragma omp for
        for(size_t i = 0; i < n; i++) {
            double x = rand_double(&seed), y = rand_double(&seed);

            if(x * x + y * y <= 1) {
#ifdef CRITICAL
#pragma omp critical
#endif
#ifdef ATOMIC
#pragma omp atomic
#endif
                inside++;
            }
        }
    }
    return (double)(4 * inside) / (double)n;
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        fprintf(stderr, "usage: %s <number-of-threads> <number-of-points>\n", argv[0]);
        return 1;
    }

    int threads = atoi(argv[1]);
    int n = atoi(argv[2]);

    double startTime = omp_get_wtime();

    double pi_aprx = monte_carlo(threads, n);

    double endTime = omp_get_wtime();

    double exc_time = endTime - startTime;

    printf("Monte Carlo Pi: %lf\n", pi_aprx);
    printf("time: %lf\n", exc_time);

    add_time(VARIANT, threads, exc_time);

    return 0;
}