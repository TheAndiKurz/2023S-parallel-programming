// Code from https://www.geeksforgeeks.org/merge-sort/

/* C program for Merge Sort */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../tools/time/time.h"

#define N 100000

#define NO_TIME

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for(i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there are any */
    while(i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there are any */
    while(j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) {
    if(l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
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

    double startTime = omp_get_wtime();
    
    mergeSort(arr, 0, arr_size - 1);
  
    double endTime = omp_get_wtime();
    double exc_time = endTime - startTime;    
    
    assert_sorted(arr, arr_size);
    char name[256];
    sprintf(name, "parallel length=%lu", arr_size);

    add_time(name, 1, exc_time);

    return 0;
}

