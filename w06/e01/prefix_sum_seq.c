#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "../../tools/time/time.h"

typedef int32_t arr_t;

int main(int argc, char *argv[]) {
    arr_t n = 0;
    if (argc == 2) {
        n = atoi(argv[1]);
    } else {
        printf("Invalid arguments! usage: %s <n>\n", argv[0]);
        exit(1);
    }

    arr_t *a = (arr_t *) malloc(n * sizeof(arr_t));
    arr_t *b = (arr_t *) malloc(n * sizeof(arr_t));

    for (arr_t i = 0; i < n; i++) {
        a[i] = 1;
    }

    double start_time = omp_get_wtime();

    b[0] = 0;
    for (arr_t i = 1; i < n; i++) {
        b[i] = b[i - 1] + a[i - 1];
    }

    double end_time = omp_get_wtime();
    double time = end_time - start_time;

    printf("Exclusive prefix sum for n=%d: %d, in %fs\n", n, b[n - 1], time);

    free(a);
    free(b);

    add_time("sequential", n, time);

    return 0;
}
