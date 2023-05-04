#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#include "../../tools/time/time.h"

//#define DEBUG

#ifdef BIG_N
    typedef int64_t arr_t;
#else 
    typedef int32_t arr_t;
#endif /* ifdef BIG_N */

//debuging helper for printing the array
void print_array(int32_t *arr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        printf("%3d ", arr[i]);
    }
    printf("\n");
}

void prefix_sum(arr_t *a, arr_t n);
void upsweep(arr_t *a, arr_t d_start, arr_t n);
void downsweep(arr_t *a, arr_t d_end, arr_t n);
void upsweep_par(arr_t *a, arr_t d_start, arr_t n);
void downsweep_par(arr_t *a, arr_t d_end, arr_t n);

// I use the algorithm outlined on https://developer.nvidia.com/gpugems/gpugems3/part-vi-gpu-computing/chapter-39-parallel-prefix-sum-scan-cuda
int main(int argc, char *argv[]) {
    arr_t n = 0;
    if (argc == 2) {
        n = (arr_t)atoi(argv[1]);
    } else {
        printf("Invalid arguments! usage: %s <n>\n", argv[0]);
        exit(1);
    }
    
    arr_t min_n = 2 << ((arr_t) log2(n-1));
    arr_t *a = (arr_t *) malloc(min_n * sizeof(arr_t));

    for (arr_t i = 0; i < min_n; i++) {
        a[i] = 1;
    }

    double start_time = omp_get_wtime();

    prefix_sum(a,min_n);

    double end_time = omp_get_wtime();
    double time = end_time - start_time;

#ifdef BIG_N
    printf("Exclusive prefix sum for n=%lld: %lld, in %fs\n", n, a[n - 1], time);
#else 
    printf("Exclusive prefix sum for n=%d: %d, in %fs\n", n, a[n - 1], time);
#endif /* ifdef BIG_N */
#ifdef DEBUG
    printf("parallel tasks n-%d/ n_threads = %d %s\n",   \
           n, omp_get_max_threads(), a[n - 1] != n-1 ? "(wrong)" : "");
#endif /* ifdef DEBUG */
  
    char msg[64];
    sprintf(msg, "parallel using tasks (%d threads)", omp_get_max_threads());
    add_time(msg, n, time);
    free(a);

    return 0;
}

void prefix_sum(arr_t* a, arr_t n) {
    // Upsweep phase
    arr_t block_size = n/omp_get_max_threads();
    #pragma omp parallel 
    {
        #pragma omp single
        {
            for (int i = 1; i < omp_get_max_threads(); i++){
                #pragma omp task
                upsweep(a+i*block_size, 0, block_size);
            }
            // let the master thread to one computation too
            upsweep(a, 0, block_size);
            // doing the last steps of upsweep 
            #pragma omp taskwait
            upsweep_par(a, log2(block_size), n);

            // doing the first steps of downsweep
            a[n-1] = 0;
            downsweep_par(a, log2(block_size), n);
            for (int i = 1; i < omp_get_max_threads(); i++){
                #pragma omp task
                downsweep(a+i*block_size, 0, block_size);
            }
            // let the master thread to one computation too
            downsweep(a, 0, block_size);
            #pragma omp taskwait
        }
    }
    return;
}

void upsweep(arr_t *a, arr_t d_start, arr_t n){
    for (arr_t d = d_start; d < (arr_t) log2(n); d++) {
        arr_t step = 1 << (d + 1);
        for (arr_t k = 0; k < n; k += step) {
            a[k + step - 1] += a[k + (step >> 1) - 1];
        }
    }
}

void downsweep(arr_t *a, arr_t d_end, arr_t n){
    for (arr_t d = (arr_t) log2(n) - 1; d >= d_end; d--) {
        arr_t step = 1 << (d + 1);
        for (arr_t k = 0; k < n; k += step) {
            arr_t t = a[k + (step >> 1) - 1];
            a[k + (step >> 1) - 1] = a[k + step - 1];
            a[k + step - 1] += t;
        }
    }
}

void upsweep_par(arr_t *a, arr_t d_start, arr_t n){
    for (arr_t d = d_start; d < (arr_t) log2(n); d++) {
        arr_t step = 1 << (d + 1);
        #pragma omp parallel for
        for (arr_t k = 0; k < n; k += step) {
            a[k + step - 1] += a[k + (step >> 1) - 1];
        }
    }
}

void downsweep_par(arr_t *a, arr_t d_end, arr_t n){
    for (arr_t d = (arr_t) log2(n) - 1; d >= d_end; d--) {
        arr_t step = 1 << (d + 1);
        #pragma omp parallel for
        for (arr_t k = 0; k < n; k += step) {
            arr_t t = a[k + (step >> 1) - 1];
            a[k + (step >> 1) - 1] = a[k + step - 1];
            a[k + step - 1] += t;
        }
    }
}
