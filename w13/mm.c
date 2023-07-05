#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// allows the user to specify the problem size at compile time
#ifndef N
        #define N 2048
#endif

#define IND(i, j) (i * N + j)

// comment out to disable verification for big matrix sizes
// #define CHECK

// block size for matrix multiplication
#define BLOCK_SIZE 128
#define ALIGNMENT 32

// initialize matrix
void initMatrix(double *A) {
    #pragma omp parallel for
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            A[IND(i, j)] = (double) N * N / (0.5 * IND(i, j));
        }
    }
}

// basic implementation for reference and result validation
void multiplyMatrixBasic(double *A, double *B, double *C) {
    
    for(size_t i = 0; i < N; i++) {
        for(size_t k = 0; k < N; k++) {
            for(size_t j = 0; j < N; j++) {
                C[IND(i, j)] += A[IND(i, k)] * B[IND(k, j)];
            }
        }
    }
}

// check matrix multiplication result
int checkMultiply(double *A, double *B, double *C) {
    double* C_check = calloc(N * N, sizeof(double));
    multiplyMatrixBasic(A, B, C_check);

    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < N; j++) {
            if(fabs(C[IND(i, j)] - C_check[IND(i, j)]) > 0.0005) {
                free(C_check);
                return 1;
            }
        }
    }

    free(C_check);
    return 0;
}

// (fast) matrix multiplication 
void transposeMatrix(double *A, double* AT) {
    #pragma omp parallel for collapse(2)
    for(size_t i = 0; i < N; i++){
        for(size_t j = 0; j < N; j++){
            AT[IND(i, j)] = A[IND(j, i)];
        }
    }
}

void multiplyMatrix(double *A, double *B, double *C) {
    
    double* B_T = NULL;
    posix_memalign(((void**)&B_T), ALIGNMENT, sizeof(double) * N * N);
    transposeMatrix(B, B_T);

    #pragma omp parallel for collapse(3)
    for(size_t ii = 0; ii < N; ii += BLOCK_SIZE){
        for(size_t jj = 0; jj < N; jj += BLOCK_SIZE){
            for(size_t kk = 0; kk < N; kk += BLOCK_SIZE){

                size_t i_lim = ii + BLOCK_SIZE < N ? ii + BLOCK_SIZE : N;
                size_t j_lim = jj + BLOCK_SIZE < N ? jj + BLOCK_SIZE : N;
                size_t k_lim = kk + BLOCK_SIZE < N ? kk + BLOCK_SIZE : N;

                for(size_t i = ii; i < i_lim; i++){
                    for(size_t j = jj; j < j_lim; j++){
                        double sum = 0;
                        #pragma omp simd reduction(+:sum) aligned(A, B_T: ALIGNMENT)
                        for(size_t k = kk; k < k_lim; k++){
                            sum += A[IND(i, k)] * B_T[IND(j, k)];
                        }
                        C[IND(i, j)] = sum;
                    }
                }
            }
        }
    }
    
    free(B_T);
}

int main() {

    // This benchmark is computing the product of two matrices
    //              C = A * B
    // where A and B are square matrices of the same size

    // feel free to change the allocation if required
    // double* A = malloc(sizeof(double) * N * N);
    // double* B = malloc(sizeof(double) * N * N);
    // double* C = calloc(N * N, sizeof(double));
    
    // allocate aligned memory adresses:
    double* A = NULL;
    double* B = NULL;
    double* C = NULL;
    posix_memalign(((void**)&A), ALIGNMENT, sizeof(double) * N * N);
    posix_memalign(((void**)&B), ALIGNMENT, sizeof(double) * N * N);
    posix_memalign(((void**)&C), ALIGNMENT, sizeof(double) * N * N);
    

    // init matrices
    initMatrix(A);
    initMatrix(B);

    double timeStart = omp_get_wtime();

    // conduct multiplication
    multiplyMatrix(A, B, C);

    double timeEnd = omp_get_wtime();

#ifdef CHECK
    int success = checkMultiply(A, B, C);
    printf("Multiplication check: %s\n", success ? "Failure" : "Success");
#endif

    printf("Time: %f\n", timeEnd-timeStart);

    free(A);
    free(B);
    free(C);

    return EXIT_SUCCESS;
}