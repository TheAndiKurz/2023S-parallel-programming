#include <assert.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../tools/time/time.h"

#define SIZE 1000
#define REPS 1000000
#define A_VAL 1.0
#define B_VAL 2.0
#define C_VAL 3.0
#define RESULT 6000001.0
#define ASSERT_EPSILON 0.001

#ifndef NAME
#define NAME "reference"
#endif

// Initialize vectors with constant values
void init(float* a, float* b, float* c, int size) {
    for(int i = 0; i < size; i++) {
        a[i] = A_VAL;
        b[i] = B_VAL;
        c[i] = C_VAL;
    }
}

// Compute a[i] += b[i] * c[i] for three float vectors a, b, and c
void compute(float* a, float* b, float* c, int size) {
    for(int run = 0; run < REPS; ++run) {
#if defined(VECTORIZE)
#pragma omp simd
#endif
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

void print(float* a, int size) {
    for(int i = 0; i < size; i++) {
        printf("%f ", a[i]);
    }
    printf("\n");
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

    // print(a, size);
    verify(a, size);

    add_time(NAME, size, time);

    return 0;
}
