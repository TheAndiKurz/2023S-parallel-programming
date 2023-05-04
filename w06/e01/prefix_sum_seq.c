#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "../../tools/time/time.h"

#ifdef BIG_N
    typedef int64_t arr_t;
#else 
    typedef int32_t arr_t;
#endif /* ifdef BIG_N */

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

#ifdef BIG_N
    printf("Exclusive prefix sum for n=%lld: %lld, in %fs\n", n, b[n - 1], time);
#else
    printf("Exclusive prefix sum for n=%d: %d, in %fs\n", n, b[n - 1], time);
#endif /* ifdef BIG_N */
#ifdef DEBUG
    printf("sequential n=%d %s\n",   \
           n, a[n - 1] != n-1 ? "(wrong)" : "");
#endif /* ifdef DEBUG */

    free(a);
    free(b);

    add_time("sequential", n, time);

    return 0;
}
