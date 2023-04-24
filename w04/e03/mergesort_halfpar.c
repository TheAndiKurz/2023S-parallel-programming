// Code from the lecture slides

/* C program for Merge Sort */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>

#include "../../tools/time/time.h"

void merge(int target[], int a[], int b[], int na, int nb) {
    int i = 0, j = 0, k = 0;
    while(i < na && j < nb){
        if (a[i] < b[i]){
            target[k] = a[i];
            i++;
        } else {
            target[k] = b[j];
            j++;
        }
        k++;
    }
    while(i < na){
        target[k] = a[i];
        i++;
        k++;
    }
    while(j < nb){
        target[k] = a[j];
        j++;
        k++;
    }
}

void merge_sort(int target[], int source[], int n) {
    if (n == 1) {
        target[0] = source[0];
    } else {
        int* temp = malloc(sizeof(int)*n);
        int m = n/2;
        #pragma omp task
            merge_sort(temp, source, m);
        #pragma omp task
            merge_sort(temp+m, source+m, n-m);
        #pragma omp taskwait
            merge(target, temp, temp+m, m, n-m);
        free(temp);
    }
}

void assert_sorted(int arr[], size_t n){
    for (size_t i = 0; i < n-1; i++){
        assert(arr[i] <= arr[i+1]);
    }

}

int main(int argc, char *argv[]) {
    if (argc != 2){
        printf("invalid arguments! usage: %s <number_elements>\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t arr_size = (size_t)strtol(argv[1], NULL, 10);
    int *arr = (int *)malloc(sizeof(int)*arr_size);
    int *target = (int *)malloc(sizeof(int)*arr_size);

    double startTime = omp_get_wtime();

    merge_sort(target, arr, arr_size);

    double endTime = omp_get_wtime();
    double exc_time = endTime - startTime;
    int threads = omp_get_max_threads();

    assert_sorted(arr, arr_size);
    free(arr);
    free(target);

    char name[256];
    sprintf(name, "parallel length=%lu", arr_size);

    add_time(name, threads, exc_time);
    return EXIT_SUCCESS;
}
