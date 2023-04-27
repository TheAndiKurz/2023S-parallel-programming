#include "../../tools/time/time.h"
#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESOLUTION_WIDTH 50
#define RESOLUTION_HEIGHT 50

#define PERROR fprintf(stderr, "%s:%d: error: %s\n", __FILE__, __LINE__, strerror(errno))
#define PERROR_GOTO(label) \
    do { \
        PERROR; \
        goto label; \
    } while(0)

#define INIT_T (273)
#define HEAT_SOURCE_T (273 + 60)

// -- vector utilities --
#define IND(y, x) ((y)*N + (x))

void printTemperature(double* m, int N, int M);

double laplaceOperator(double* A, int cols, int rows, int indX, int indY);

// -- simulation code ---

int main(int argc, char** argv) {
    // 'parsing' optional input parameter = problem size
    int N = 200;
    if(argc > 1) {
        N = atoi(argv[1]);
    }
    int T = N * 10;
    printf("Computing heat-distribution for room size %dX%d for T=%d timesteps\n", N, N, T);

    // ---------- setup ----------

    // create a buffer for storing temperature fields
    double* A = malloc(sizeof(double) * N * N);

    if(!A) PERROR_GOTO(error_a);

    // set up initial conditions in A
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            A[IND(i, j)] = INIT_T; // temperature is 0° C everywhere (273 K)
        }
    }

    // and there is a heat source
    int source_x = N / 4;
    int source_y = N / 4;
    A[IND(source_x, source_y)] = HEAT_SOURCE_T;

    printf("Initial:\n");
    printTemperature(A, N, N);
    printf("\n");

    // ---------- compute ----------

    // create a second buffer for the computation
    double* B = malloc(sizeof(double) * N * N);
    if(!B) PERROR_GOTO(error_b);

    double startTime = omp_get_wtime();

    // for each time step ..
    for(int t = 0; t < T; t++) {

// .. we propagate the temperature
#ifdef PARALLEL
#pragma omp parallel for collapse(2)
#endif
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                B[IND(i, j)] = A[IND(i, j)] + laplaceOperator(A, N, N, i, j);
            }
        }

        B[IND(source_x, source_y)] = HEAT_SOURCE_T; // restore heat source

        // swap matrices (just pointers, not content)
        double* swp = A;
        A = B;
        B = swp;

        // every 1000 steps show intermediate step
        if(!(t % 1000)) {
            printf("Step t=%d\n", t);
            printTemperature(A, N, N);
            printf("\n");
        }
    }

    double endTime = omp_get_wtime();
    double exc_time = endTime - startTime;
    printf("time: %lf\n", exc_time);

    char name[TIME_CELL_LEN];
    snprintf(name, TIME_CELL_LEN, "N=%d", N);

#ifdef PARALLEL
    int threads = omp_get_max_threads();
#else
    int threads = 1;
#endif
    add_time(name, threads, exc_time);
    // ---------- check ----------

    printf("Final:");
    printTemperature(A, N, N);
    printf("\n");

    // simple verification if nowhere the heat is more then the heat source
    int success = 1;
    for(long long i = 0; i < N; i++) {
        for(long long j = 0; j < N; j++) {
            double temp = A[IND(i, j)];
            if(INIT_T <= temp && temp <= HEAT_SOURCE_T) continue;
            success = 0;
            break;
        }
    }

    printf("Verification: %s\n", (success) ? "OK" : "FAILED");

// todo ---------- cleanup ----------
error_b:
    free(B);
error_a:
    free(A);
    return (success) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void printTemperature(double* m, int N, int M) {
    const char* colors = " .-:=+*^X#%@";
    const int numColors = 12;

    // boundaries for temperature (for simplicity hard-coded)
    const double max = 273 + 30;
    const double min = 273 + 0;

    // set the 'render' resolution
    int W = RESOLUTION_WIDTH;
    int H = RESOLUTION_HEIGHT;

    // step size in each dimension
    int sW = N / W;
    int sH = M / H;

    // upper wall
    printf("\t");
    for(int u = 0; u < W + 2; u++) {
        printf("X");
    }
    printf("\n");
    // room
    for(int i = 0; i < H; i++) {
        // left wall
        printf("\tX");
        // actual room
        for(int j = 0; j < W; j++) {
            // get max temperature in this tile
            double max_t = 0;
            for(int x = sH * i; x < sH * i + sH; x++) {
                for(int y = sW * j; y < sW * j + sW; y++) {
                    max_t = (max_t < m[IND(x, y)]) ? m[IND(x, y)] : max_t;
                }
            }
            double temp = max_t;

            // pick the 'color'
            int c = ((temp - min) / (max - min)) * numColors;
            c = (c >= numColors) ? numColors - 1 : ((c < 0) ? 0 : c);

            // print the average temperature
            printf("%c", colors[c]);
        }
        // right wall
        printf("X\n");
    }
    // lower wall
    printf("\t");
    for(int l = 0; l < W + 2; l++) {
        printf("X");
    }
    printf("\n");
}

#define H 2

double laplaceOperator(double* A, int N, int M, int indX, int indY) {
    double center = A[IND(indX, indY)];

    double left = (indX - H) < 0 ? center : A[IND(indX - H, indY)];
    double right = (indX + H) >= N ? center : A[IND(indX + H, indY)];
    double top = (indY - H) < 0 ? center : A[IND(indX, indY - H)];
    double bottom = (indY + H) >= M ? center : A[IND(indX, indY + H)];

    return (left + right + top + bottom - 4 * center) / (H * H);
}