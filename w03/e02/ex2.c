#include <errno.h>
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PERROR fprintf(stderr, "%s:%d: error: %s\n", __FILE__, __LINE__, strerror(errno))
#define PERROR_GOTO(label) \
    do { \
        PERROR; \
        goto label; \
    } while(0)

#define INIT_ARRAY(arr, label) \
    do { \
        if(!(arr)) PERROR_GOTO(label); \
        for(long i = 0; i < n; ++i) { \
            (arr)[i] = malloc(sizeof(**(arr)) * n); \
            if(!(arr)[i]) PERROR_GOTO(label); \
        } \
    } while(0)

#if defined(OPTIMIZED) || defined(PADDING)

#define CACHE_LINE_SIZE 64

struct aligned_local_res {
    unsigned res;
    char padding[CACHE_LINE_SIZE - sizeof(unsigned)];
};

#endif

void free_2d_array(int** arr, long len) {
    if(!arr) {
        return;
    }
    for(long i = 0; i < len; ++i) {
        if(!arr[i]) {
            break;
        }
        free(arr[i]);
    }
    free(arr);
}

int main(int argc, char** argv) {
    // handle input
    if(argc != 2) {
        fprintf(stderr, "Error: usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    errno = 0;
    char* str = argv[1];
    char* endptr;
    long n = strtol(str, &endptr, 0);
    if(errno != 0) {
        perror("strtol");
        return EXIT_FAILURE;
    }
    if(endptr == str) {
        fprintf(stderr, "Error: no digits were found!\n");
        return EXIT_FAILURE;
    }
    if(n < 0) {
        fprintf(stderr, "Error: matrix size must not be negative!\n");
        return EXIT_FAILURE;
    }

    // allocate memory
    int status = EXIT_FAILURE;
    int** a = malloc(sizeof(*a) * n);
    INIT_ARRAY(a, error_a);
    int** b = malloc(sizeof(*b) * n);
    INIT_ARRAY(b, error_b);
    int** c = malloc(sizeof(*c) * n);
    INIT_ARRAY(c, error_c);
#if defined(OPTIMIZED) || defined(PADDING)
    struct aligned_local_res* local_res = malloc(omp_get_max_threads() * sizeof(*local_res));
#else
    unsigned* local_res = malloc(omp_get_max_threads() * sizeof(*local_res));
#endif
    if(!local_res) PERROR_GOTO(error_c);
    status = EXIT_SUCCESS;

    // fill matrix
    srand(7);
    for(long i = 0; i < n; ++i) {
        for(long j = 0; j < n; ++j) {
            a[i][j] = rand();
            b[i][j] = rand();
        }
    }

    double start_time = omp_get_wtime();
#pragma omp parallel default(none) shared(n, a, b, c, local_res)
    {
        // matrix multiplication
#if defined(OPTIMIZED) || defined(BLOCK)

        int block_size = n / (omp_get_max_threads());
        block_size = block_size < 1 ? 1 : block_size;

#pragma omp parallel for default(none) shared(n, a, b, c, block_size)
        for(long row_block = 0; row_block < n; row_block += block_size) {
            for(long col_block = 0; col_block < n; col_block += block_size) {
                for(long k_block = 0; k_block < n; k_block += block_size) {
                    for(long i = row_block; i < row_block + block_size && i < n; ++i) {
                        for(long j = col_block; j < col_block + block_size && j < n; ++j) {
                            for(long k = k_block; k < k_block + block_size && k < n; ++k) {
                                c[i][j] += a[i][k] * b[k][j];
                            }
                        }
                    }
                }
            }
        }

#else

#pragma omp parallel for default(none) shared(n, a, b, c)
        for(long i = 0; i < n; ++i) {
            for(long j = 0; j < n; ++j) {
                for(long k = 0; k < n; ++k) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }

#endif

        // sum of matrix c
#pragma omp parallel for default(none) shared(n, a, b, c, local_res)
        for(long i = 0; i < n; ++i) {
            for(long j = 0; j < n; ++j) {

#if defined(OPTIMIZED) || defined(PADDING)

                local_res[omp_get_thread_num()].res += c[i][j];

#else

                local_res[omp_get_thread_num()] += c[i][j];

#endif
            }
        }
    }
    unsigned long res = 0;
    for(int l = 0; l < omp_get_num_threads(); ++l) {

#if defined(OPTIMIZED) || defined(PADDING)

        res += local_res[l].res;

#else

        res += local_res[l];

#endif
    }
    double end_time = omp_get_wtime();
    printf("res: %lu, time: %2.2f seconds\n", res, end_time - start_time);

    // cleanup
    free(local_res);
error_c:
    free_2d_array(c, n);
error_b:
    free_2d_array(b, n);
error_a:
    free_2d_array(a, n);
    return status;
}
