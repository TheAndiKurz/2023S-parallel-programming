#include <assert.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../tools/time/time.h"

#define SIZE 1000
#define REPS 1000000
#define A_VAL 1.0f
#define B_VAL 2.0f
#define C_VAL 3.0f
#define RESULT 6000001.0f
#define ASSERT_EPSILON 0.001f

#ifndef NAME
#define NAME "auto vectorize"
#endif

// Initialize vectors with constant values
void init(float* restrict a, float* restrict b, float* restrict c, int size) {
    for(int i = 0; i < size; i++) {
        a[i] = A_VAL;
        b[i] = B_VAL;
        c[i] = C_VAL;
    }
}

// Compute a[i] += b[i] * c[i] for three float vectors a, b, and c
void compute(float* restrict a, float* restrict b, float* restrict c, int size) {
    for(int run = 0; run < REPS; ++run) {
        for(int i = 0; i < size; ++i) {
            a[i] += b[i] * c[i];
        }
    }
}

void verify(float* a, int size) {
    for(int i = 0; i < size; i++) {
        assert(a[i] - RESULT < ASSERT_EPSILON);
    }
}

int main(int argc, char* argv[]) {
    int size = SIZE;
    if(argc > 1) {
        size = atoi(argv[1]);
    }

    // init vectors
    float a[size], b[size], c[size];
    init(a, b, c, size);

    double start_time = omp_get_wtime();

    compute(a, b, c, size);

    double end_time = omp_get_wtime();
    double time = end_time - start_time;

    verify(a, size);

    add_time(NAME, size, time);

    return 0;
}
