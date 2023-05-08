#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../tools/time/time.h"

typedef int32_t arr_t;

// debuging helper for printing the array
void print_array(int32_t* arr, size_t n) {
    for(size_t i = 0; i < n; i++) {
        printf("%3d ", arr[i]);
    }
    printf("\n");
}

void prefix_sum(arr_t* a, arr_t n);
void upsweep(arr_t* a, arr_t d_start, arr_t n);
void downsweep(arr_t* a, arr_t d_end, arr_t n);
void upsweep_par(arr_t* a, arr_t d_start, arr_t n);
void downsweep_par(arr_t* a, arr_t d_end, arr_t n);

// I use the algorithm outlined on
// https://developer.nvidia.com/gpugems/gpugems3/part-vi-gpu-computing/chapter-39-parallel-prefix-sum-scan-cuda
int main(int argc, char* argv[]) {
    arr_t n = 0;
    if(argc == 2) {
        n = (arr_t)atoi(argv[1]);
    } else {
        printf("Invalid arguments! usage: %s <n>\n", argv[0]);
        exit(1);
    }

    arr_t min_n = 2 << ((arr_t)log2(n - 1));
    arr_t* a = (arr_t*)malloc(min_n * sizeof(arr_t));

    for(arr_t i = 0; i < min_n; i++) {
        a[i] = 1;
    }

    double start_time = omp_get_wtime();

    prefix_sum(a, min_n);

    double end_time = omp_get_wtime();
    double time = end_time - start_time;

    printf("Exclusive prefix sum for n=%d: %d, in %fs\n", n, a[n - 1], time);

    char msg[64];
    sprintf(msg, "parallel using for (%d threads)", omp_get_max_threads());
    add_time(msg, n, time);
    free(a);

    return 0;
}

void prefix_sum(arr_t* a, arr_t n) {
    // Upsweep phase
    arr_t block_size = n / omp_get_max_threads();

#pragma omp parallel for
    for(int i = 0; i < omp_get_max_threads(); i++) {
        upsweep_par(a + i * block_size, 0, block_size);
    }
    // doing the last steps of upsweep
    upsweep_par(a, log2(block_size), n);

    // doing the first steps of downsweep
    a[n - 1] = 0;
    downsweep_par(a, log2(block_size), n);
#pragma omp parallel for
    for(int i = 0; i < omp_get_max_threads(); i++) {
        downsweep_par(a + i * block_size, 0, block_size);
    }
    return;
}

void upsweep(arr_t* a, arr_t d_start, arr_t n) {
    for(arr_t d = d_start; d < (arr_t)log2(n); d++) {
        arr_t step = 1 << (d + 1);
        for(arr_t k = 0; k < n; k += step) {
            a[k + step - 1] += a[k + (step >> 1) - 1];
        }
    }
}

void downsweep(arr_t* a, arr_t d_end, arr_t n) {
    for(arr_t d = (arr_t)log2(n) - 1; d >= d_end; d--) {
        arr_t step = 1 << (d + 1);
        for(arr_t k = 0; k < n; k += step) {
            arr_t t = a[k + (step >> 1) - 1];
            a[k + (step >> 1) - 1] = a[k + step - 1];
            a[k + step - 1] += t;
        }
    }
}

void upsweep_par(arr_t* a, arr_t d_start, arr_t n) {
    for(arr_t d = d_start; d < (arr_t)log2(n); d++) {
        arr_t step = 1 << (d + 1);
#pragma omp parallel for
        for(arr_t k = 0; k < n; k += step) {
            a[k + step - 1] += a[k + (step >> 1) - 1];
        }
    }
}

void downsweep_par(arr_t* a, arr_t d_end, arr_t n) {
    for(arr_t d = (arr_t)log2(n) - 1; d >= d_end; d--) {
        arr_t step = 1 << (d + 1);
#pragma omp parallel for
        for(arr_t k = 0; k < n; k += step) {
            arr_t t = a[k + (step >> 1) - 1];
            a[k + (step >> 1) - 1] = a[k + step - 1];
            a[k + step - 1] += t;
        }
    }
}
