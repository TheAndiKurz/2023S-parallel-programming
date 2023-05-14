#include "../../tools/time/time.h"
#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CHECK_STRTOL(errno, endptr, strptr, message) \
    do { \
        if(errno != 0 || *endptr != '\0' || endptr == strptr) { \
            perror(message); \
            return EXIT_FAILURE; \
        } \
    } while(0)

int main(int argc, char* argv[]) {

    /* INPUT */

    if(argc != 2) {
        fprintf(stderr, "usage: ./task2 <vector_size> \n");
        return EXIT_FAILURE;
    }

    char* endptr;
    errno = 0;
    int vector_size = strtol(argv[1], &endptr, 10); // converting number string to int
    CHECK_STRTOL(errno, endptr, argv[1], "strtol number");

    /* DATA INITIALISATION */

    float* a = malloc(vector_size * sizeof(float));
    float* b = malloc(vector_size * sizeof(float));
    float* c = malloc(vector_size * sizeof(float));
    for(int i = 0; i < vector_size; i++) {
        a[i] = 1.0f;
        b[i] = 2.0f;
        c[i] = 3.0f;
    }

    /* ALGORITHM */
    int repetitions = 1e6;

    time_t start_time = omp_get_wtime();
    for(int run = 0; run < repetitions; ++run) {
        for(int i = 0; i < vector_size; ++i) {
            a[i] += b[i] * c[i];
        }
    }
    time_t end_time = omp_get_wtime();
    time_t exec_time = end_time - start_time;
    long threads = omp_get_max_threads();
    char* variant = getenv("VARIANT");
    variant = variant == NULL ? "NO VARIANT" : variant;
    add_time_value(variant, threads, exec_time, vector_size);

    printf("Time: %ld s\n", end_time - start_time);
    printf("Result: %f\n", a[vector_size - 1]);
    free(a);
    free(b);
    free(c);
    return EXIT_SUCCESS;
}
