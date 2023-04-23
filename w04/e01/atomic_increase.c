#include "../../tools/time/time.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void atomic_increase(size_t iterations) {
    int counter = 0;

#pragma omp parallel for
    for(size_t i = 0; i < iterations; i++) {
#pragma omp atomic
        counter++;
    }
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        fprintf(stderr, "usage: %s <number-of-iterations>\n", argv[0]);
        exit(1);
    }

    int threads = omp_get_max_threads();
    printf("threads: %d\n", threads);

    int n = atoi(argv[1]);
    printf("iterations: %d\n", n);

    double startTime = omp_get_wtime();

    atomic_increase(n);

    double endTime = omp_get_wtime();

    double exc_time = endTime - startTime;

    printf("time: %lf\n", exc_time);

    char name[TIME_CELL_LEN];
    snprintf(name, TIME_CELL_LEN, "places=%s affinity=%s %d", getenv("OMP_PLACES"),
             getenv("OMP_PROC_BIND"), n);

    add_time(name, threads, exc_time);

    return 0;
}