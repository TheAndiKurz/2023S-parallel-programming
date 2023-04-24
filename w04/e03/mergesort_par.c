// Code from the lecture slides

/* C program for Merge Sort */
#include <stdio.h>
#include <stdlib.h>

#include "../../tools/time/time.h"

#define N 100000
#ifndef THREADS
#define THREADS 1
#endif /* !THREADS */


int binary_search(int v, int arr[], int n){
    int m = n/2;
    if (arr[m] == v){
      return m;
    } else if (v < arr[m]) {
        return binary_search(v, arr, m)
    } else {
        return binary_search(v, arr+m, n-m)
    }
}

void merge(int C[], int A[], int B[], int na, int nb) {
    if (na < nb) {
        merge(C, B, A, nb, na);
    } else if {
        return;
    } else {
        int ma = na/2;
        int mb = binary_search(A[ma], B, nb);
        C[ma+mb] = A[ma]
        #pragma omp task 
            merge(C,A,B,ma,mb);
        #pragma omp task
            merge(C+ma+mb+1,A+ma+1,B+mb,na-ma-1,nb-mb);
        #pragma omp taskwait
    }
}

void merge_sort(int B[], int A[], int n) {
    if (n == 1) {
        B[0] = A[0]
    } else {
        int C[n] = {0}; 
        #pragma omp task
            mergeSort(C, A, n/2);
        #pragma omp task
            mergeSort(C+n/2, A+n/2, n-n/2);
        #pragma omp taskwait
            merge(B, C, C+n/2, n/2, n-n/2);
    }
}

void assert_sorted(int arr[], size_t n){
    for (size_t i = 0; i < n-1; i++){
        assert(arr[i] <= arr[i+1]);
    }

}

int main(void) {
    int *arr = (int *)malloc(sizeof(int)*N);
    size_t arr_size = N;

    double startTime = omp_get_wtime();
  
    mergeSort(arr, 0, arr_size - 1);

    double endTime = omp_get_wtime();
    double exc_time = endTime - startTime;    
    printf("Merge sort seqential: %lf seconds\n", exc_time);
    
    assert_sorted(arr, arr_size);

    add_time("mergesort seqential", 1, exc_time);

    return 0;
}
