/* Write a sequential program that computes a[i] += b[i] * c[i] for three float vectors a, b, and c. Enclose this computation in a loop such that it is repeated 1e6 times. I.e. your code should look like this:
for(int run = 0; run < repetitions; ++run) {
    for(int i = 0; i < size; ++i) {
        a[i] += b[i] * c[i];
    }
}
Initialize the vectors with constant values and add some output that allows you to verify correct computation of the program for subsequent optimization steps (try to avoid overflows). Compile this program on LCC2 with gcc 10.3.0 using -O1 and measure the execution time of the computation only for several problem sizes (=vector lengths). This sequential program is our baseline reference.

Try to use auto-vectorization in the compiler to vectorize the computation. Investigate which flag(s) to use for that, and try to limit your compiler change to only enable vectorization but not any other optimizations. Measure the execution time for the same problem sizes as before and compute the respective speedups. What can you observe in terms of performance? Is the result still correct? Does varying the problem size affect the performance gain or loss?
*/

// compile with: gcc -O1 -fopt-info-vec -fopt-info-vec-missed -fopt-info-vec-note -mavx -march=native -o auto_vec auto_vec.c
// run with: ./auto_vec 1000

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
    #define NAME "auto vectorize"
#endif


// Initialize vectors with constant values
void init(float *a, float *b, float *c, int size) {
    for (int i = 0; i < size; i++) {
        a[i] = A_VAL;
        b[i] = B_VAL;
        c[i] = C_VAL;
    }
}

// Compute a[i] += b[i] * c[i] for three float vectors a, b, and c
void compute(float *a, float *b, float *c, int size) {
    for (int run = 0; run < REPS; ++run) {
        for (int i = 0; i < size; ++i) {
            a[i] += b[i] * c[i];
        }
    }
}

void verify(float *a, int size) {
    for (int i = 0; i < size; i++){
        assert(a[i] - RESULT < ASSERT_EPSILON);
    }
}

void print(float *a, int size) {
    for (int i = 0; i < size; i++) {
        printf("%f ", a[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int size = SIZE;
    if (argc > 1) {
        size = atoi(argv[1]);
    }

    // init vectors
    float a[size], b[size], c[size]; 
    init(a, b, c, size);

    double start_time = omp_get_wtime();

    compute(a, b, c, size);

    double end_time = omp_get_wtime();
    double time = end_time - start_time;

    //print(a, size);
    verify(a, size);

    add_time( NAME , size, time);

    return 0;
}
