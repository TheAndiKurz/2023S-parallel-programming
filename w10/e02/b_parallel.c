#include "../../tools/time/time.h"
#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define GET_INTEGER_ERROR "Failed to parse argument. Make sure you entered a valid int!\n"

// NOTE: This macro will set errno to `invalid argument` if strtol failed without setting errno
#define CHECK_STRTOL(errno, endptr, strptr, message)                                               \
    do {                                                                                           \
        if(errno != 0 || *endptr != '\0' || endptr == strptr) {                                    \
            errno = errno == 0 ? EINVAL : errno;                                                   \
            perror(message);                                                                       \
        }                                                                                          \
    } while(0)

int main(int argc, char* argv[]) {
    /* Setup */
    if(argc != 2) {
        fprintf(stderr, "Usage: ./<binary> <array_size>\n Expected 1 argument received %d",
                argc - 1);
    }
    printf("setup\n");
    char* endptr;
    errno = 0;
    long n = strtol(argv[1], &endptr, 10);
    CHECK_STRTOL(errno, endptr, argv[1], GET_INTEGER_ERROR);

    const size_t DOUBLE_ARRAY_SIZE = n * sizeof(double);
    double* x = malloc(DOUBLE_ARRAY_SIZE);
    double* y = malloc(DOUBLE_ARRAY_SIZE);
    double* z = malloc(DOUBLE_ARRAY_SIZE);

    srand(42);
    for(int i = 0; i < n; i++) {
        x[i] = rand();
        y[i] = rand();
        z[i] = rand();
    }
    printf("setup finished\n");

    /* Calculate */
    //---------------------------------------------------------------------------------------------
    double start_time = omp_get_wtime();
    /* NOTE:
     * There exists a loop carried true dependence from S1 to S2 (S1 d S2) with (<)
     * loop distribution is applicable
     */
#pragma omp parallel
    {

#pragma omp for
        for(int i = 1; i < n; i++) {
            y[i] = y[i] + z[i] * 3; // S2
        }
#pragma omp for
        for(int i = 1; i < n; i++) {
            x[i] = (x[i] + y[i - 1]) / 2; // S1
        }
    }
    //---------------------------------------------------------------------------------------------
    double end_time = omp_get_wtime();

    /* CSV */
    double time = end_time - start_time;
    int threads = omp_get_max_threads();
    add_time("b parallel", threads, time);
    printf("last x = %f", x[n - 1]);
    printf("last y = %f", y[n - 1]);
    printf("last z = %f\n", z[n - 1]);

    /* Free */
    free(x);
    free(y);
    free(z);
    return EXIT_SUCCESS;
}
