#include "../../tools/time/time.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double rand_double(unsigned* seed) {
    return (double)rand_r(seed) / (double)RAND_MAX;
}

double monte_carlo(size_t threads, size_t n) {
    unsigned seed = time(NULL);
    size_t sum = 0;
#pragma omp parallel num_threads(threads)
{
	size_t inside = 0;
#pragma omp for
	    for(size_t i = 0; i < n; i++) {
		double x = rand_double(&seed), y = rand_double(&seed);

		if(x * x + y * y <= 1) {
		    inside++;
		}
	    }
#pragma omp atomic
    sum += inside;
}
    return (double)(4 * sum) / (double)n;
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

    add_time_value("local_sum", threads, exc_time, pi_aprx);

    return 0;
}
