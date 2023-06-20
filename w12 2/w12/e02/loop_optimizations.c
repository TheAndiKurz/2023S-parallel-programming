#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>

#define N 10
#define BLOCK_SIZE 64 / sizeof(double)

#define VERSION A

void wrapper();

int main(void) {
    wrapper();
    return 0;
}

#if VERSION == A

void a_func(int* a, int* b) {
    for (int i = 0; i < N - 1; ++i) {
        a[i] = b[i] + b[i + 1];
    }
}

void wrapper() {
    int* a = malloc(N * sizeof(int));
    int* b = malloc(N * sizeof(int));
    #ifdef TIME
    double start = omp_get_wtime();
    #endif
    a_func(a, b);
    #ifdef TIME
    double end = omp_get_wtime();
    printf("Time: %f\n", end - start);
    #endif
    int sum = 0;
    for (int i = 0 ; i < N; ++i) {
        sum += a[i];
        sum += b[i];
    }
    printf("Sum: %d\n", sum);
}

#elif VERSION == A_SOL

void a_sol_func(int* a, int* b) {
    for (int i = 0; i < N - 2; i += 2) {
        a[i] = b[i] + b[i + 1];
        a[i + 1] = b[i + 1] + b[i + 2];
    }
}

void wrapper() {
    int* a = malloc(N * sizeof(int));
    int* b = malloc(N * sizeof(int));
    #ifdef TIME
    double start = omp_get_wtime();
    #endif
    a_sol_func(a, b);
    #ifdef TIME
    double end = omp_get_wtime();
    printf("Time: %f\n", end - start);
    #endif
    int sum = 0;
    for (int i = 0 ; i < N; ++i) {
        sum += a[i];
        sum += b[i];
    }
    printf("Sum: %d\n", sum);
}

#elif VERSION == B

void b_func(double* a) {
    for (int i = 0; i < N; ++i) {
        a[i] *= hypot(0.3, 0.4);
    }
}

void wrapper() {
    double *a = malloc(N * sizeof(double));
    #ifdef TIME
    double start = omp_get_wtime();
    #endif
    b_func(a);
    #ifdef TIME
    double end = omp_get_wtime();
    printf("Time: %f\n", end - start);
    #endif
    double sum = 0;
    for (int i = 0 ; i < N; ++i) {
        sum += a[i];
    }
    printf("Sum: %f\n", sum);
}

#elif VERSION == B_SOL

void b_sol_func_func(double* a) {
    double hyp = hypot(0.3, 0.4);
    for (int i = 0; i < N; ++i) {
        a[i] *= hyp;
    }
}

void wrapper() {
    double *a = malloc(N * sizeof(double));
    #ifdef TIME
    double start = omp_get_wtime();
    #endif
    b_sol_func_func(a);
    #ifdef TIME
    double end = omp_get_wtime();
    printf("Time: %f\n", end - start);
    #endif
    double sum = 0;
    for (int i = 0 ; i < N; ++i) {
        sum += a[i];
    }
    printf("Sum: %f\n", sum);
}

#elif VERSION == C

void c(int* a, int* b, int* c) {
    for (int i = 0; i < N; ++i) {
        if (N % 2) {
            a[i] = b[i] + 5;
        } else {
            a[i] = c[i] + 5;
        }
    }
}

void wrapper() {
    int* a = malloc(N * sizeof(int));
    int* b = malloc(N * sizeof(int));
    int* c = malloc(N * sizeof(int));
    #ifdef TIME
    double start = omp_get_wtime();
    #endif
    c(a, b, c);
    #ifdef TIME
    double end = omp_get_wtime();
    printf("Time: %f\n", end - start);
    #endif
    int sum = 0;
    for (int i = 0 ; i < N; ++i) {
        sum += a[i];
        sum += b[i];
        sum += c[i];
    }
    printf("Sum: %d\n", sum);
}

#elif VERSION == C_SOL

void c_sol_func(int* a, int* b, int* c) {
    int *arr = (N % 2) ? b : c;
    for (int i = 0; i < N; ++i) {
        a[i] = arr[i] + 5;
    }
}

void wrapper() {
    int* a = malloc(N * sizeof(int));
    int* b = malloc(N * sizeof(int));
    int* c = malloc(N * sizeof(int));
    #ifdef TIME
    double start = omp_get_wtime();
    #endif
    c_sol_func(a, b, c);
    #ifdef TIME
    double end = omp_get_wtime();
    printf("Time: %f\n", end - start);
    #endif
    int sum = 0;
    for (int i = 0 ; i < N; ++i) {
        sum += a[i];
        sum += b[i];
        sum += c[i];
    }
    printf("Sum: %d\n", sum);
}

#elif VERSION == D

void d_func(int* a, int* b, int* c) {
    int sum_a = 0, sum_b = 0, sum_c = 0;
    for (int i = 0; i < N; ++i) {
        sum_a += a[i];
        sum_b += b[i];
        sum_c += c[i];
    }
    return sum_a + sum_b + sum_c;
}

void wrapper() {
    int* a = malloc(N * sizeof(int));
    int* b = malloc(N * sizeof(int));
    int* c = malloc(N * sizeof(int));
    #ifdef TIME
    double start = omp_get_wtime();
    #endif
    d_func(a, b, c);
    #ifdef TIME
    double end = omp_get_wtime();
    printf("Time: %f\n", end - start);
    #endif
    int sum = 0;
    for (int i = 0 ; i < N; ++i) {
        sum += a[i];
        sum += b[i];
        sum += c[i];
    }
    printf("Sum: %d\n", sum);
}

#elif VERSION == D_SOL

void d_sol_func(int* a, int* b, int* c) {
    int sum_a = 0, sum_b = 0, sum_c = 0;
    for (int i = 0; i < N; ++i) {
        sum_a += a[i];
    }
    for (int i = 0; i < N; ++i) {
        sum_b += b[i];
    }
    for (int i = 0; i < N; ++i) {
        sum_c += c[i];
    }
    return sum_a + sum_b + sum_c;
}

void wrapper() {
    int* a = malloc(N * sizeof(int));
    int* b = malloc(N * sizeof(int));
    int* c = malloc(N * sizeof(int));
    #ifdef TIME
    double start = omp_get_wtime();
    #endif
    d_sol_func(a, b, c);
    #ifdef TIME
    double end = omp_get_wtime();
    printf("Time: %f\n", end - start);
    #endif
    int sum = 0;
    for (int i = 0 ; i < N; ++i) {
        sum += a[i];
        sum += b[i];
        sum += c[i];
    }
    printf("Sum: %d\n", sum);
}

#elif VERSION == E

void e_func(int* a) {
    int min = a[0];
    int sum = 0;
    for (int i = 1; i < N; ++i) {
        min = (a[i] < min) ? a[i] : min;
    }
    for (int i = 0; i < N; ++i) {
        sum += a[i];
    }
    return min + sum;
}

void wrapper() {
    int* a = malloc(N * sizeof(int));
    #ifdef TIME
    double start = omp_get_wtime();
    #endif
    e_func(a);
    #ifdef TIME
    double end = omp_get_wtime();
    printf("Time: %f\n", end - start);
    #endif
    int sum = 0;
    for (int i = 0 ; i < N; ++i) {
        sum += a[i];
    }
    printf("Sum: %d\n", sum);
}

#elif VERSION == E_SOL

void e_sol_func(int* a) {
    int min = a[0];
    int sum = a[0];
    for (int i = 1; i < N; ++i) {
        min = (a[i] < min) ? a[i] : min;
        sum += a[i];
    }
    return min + sum;
}

void wrapper() {
    int* a = malloc(N * sizeof(int));
    #ifdef TIME
    double start = omp_get_wtime();
    #endif
    e_sol_func(a);
    #ifdef TIME
    double end = omp_get_wtime();
    printf("Time: %f\n", end - start);
    #endif
    int sum = 0;
    for (int i = 0 ; i < N; ++i) {
        sum += a[i];
    }
    printf("Sum: %d\n", sum);
}

#elif VERSION == F

void f_func(int* a, int* b, int* c) {
    for (int i = 0; i < N; ++i) {
        if (i % 2) {
            a[i] = b[i] + 4;
        } else {
            a[i] = c[i] + 5;
        }
    }
}

void wrapper() {
    int* a = malloc(N * sizeof(int));
    int* b = malloc(N * sizeof(int));
    int* c = malloc(N * sizeof(int));
    #ifdef TIME
    double start = omp_get_wtime();
    #endif
    f_func(a, b, c);
    #ifdef TIME
    double end = omp_get_wtime();
    printf("Time: %f\n", end - start);
    #endif
    int sum = 0;
    for (int i = 0 ; i < N; ++i) {
        sum += a[i];
        sum += b[i];
        sum += c[i];
    }
    printf("Sum: %d\n", sum);
}

#elif VERSION == F_SOL

void f_sol_func(int* a, int* b, int* c) {
    for (int i = 0; i < N; i += 2) {
        a[i] = c[i] + 5;
    }
    for (int i = 1; i < N; i += 2) {
        a[i] = b[i] + 4;
    }
}

void wrapper() {
    int* a = malloc(N * sizeof(int));
    int* b = malloc(N * sizeof(int));
    int* c = malloc(N * sizeof(int));
    #ifdef TIME
    double start = omp_get_wtime();
    #endif
    f_sol_func(a, b, c);
    #ifdef TIME
    double end = omp_get_wtime();
    printf("Time: %f\n", end - start);
    #endif
    int sum = 0;
    for (int i = 0 ; i < N; ++i) {
        sum += a[i];
        sum += b[i];
        sum += c[i];
    }
    printf("Sum: %d\n", sum);
}

#elif VERSION == G

void g_func(int** a, int** b, int** c) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                c[i][j] = a[i][k] * b[k][j];
            }
        }
    }
}

void wrapper() {
    int** a = (int**) malloc(N * sizeof(int*));
    int** b = (int**) malloc(N * sizeof(int*));
    int** c = (int**) malloc(N * sizeof(int*));
    for (int i = 0; i < N; ++i) {
        a[i] = (int*) malloc(N * sizeof(int));
        b[i] = (int*) malloc(N * sizeof(int));
        c[i] = (int*) malloc(N * sizeof(int));
    }
    #ifdef TIME
    double start = omp_get_wtime();
    #endif
    g_func(a, b, c);
    #ifdef TIME
    double end = omp_get_wtime();
    printf("Time: %f\n", end - start);
    #endif
    int sum = 0;
    for (int i = 0 ; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            sum += a[i][j];
            sum += b[i][j];
            sum += c[i][j];
        }
    }
    printf("Sum: %d\n", sum);
}

#elif VERSION == G_SOL

void g_sol_func(int** a, int** b, int** c) {
    for (int ic = 0; ic < N; ic += BLOCK_SIZE) {
        for (int jc = 0; jc < N; jc += BLOCK_SIZE) {
            int i_lim = (ic + BLOCK_SIZE < N) ? ic + BLOCK_SIZE : N;
            int j_lim = (jc + BLOCK_SIZE < N) ? jc + BLOCK_SIZE : N;
            for (int i = ic; i < i_lim; ++i) {
                for (int j = jc; j < j_lim; ++j) {
                    c[i][j] = a[i][N - 1] * b[N - 1][j];
                }
            }
        }
    }
}

void wrapper() {
    int** a = (int**) malloc(N * sizeof(int*));
    int** b = (int**) malloc(N * sizeof(int*));
    int** c = (int**) malloc(N * sizeof(int*));
    for (int i = 0; i < N; ++i) {
        a[i] = (int*) malloc(N * sizeof(int));
        b[i] = (int*) malloc(N * sizeof(int));
        c[i] = (int*) malloc(N * sizeof(int));
    }
    #ifdef TIME
    double start = omp_get_wtime();
    #endif
    g_sol_func(a, b, c);
    #ifdef TIME
    double end = omp_get_wtime();
    printf("Time: %f\n", end - start);
    #endif
    int sum = 0;
    for (int i = 0 ; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            sum += a[i][j];
            sum += b[i][j];
            sum += c[i][j];
        }
    }
    printf("Sum: %d\n", sum);
}

#endif