#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>

#include "../../tools/time/time.h"

#define VECTOR_SIZE 2048

#ifdef VECTORICE
#define NAME "vectorized"
void calculate_sum_and_mult(float* a, float* b, float* c, size_t size) {
    for(size_t i = 0; i < size; i += 4) {
        // Load 4 floats from memory into SSE registers
        __m128 a_data = _mm_load_ps(&a[i]);
        __m128 b_data = _mm_load_ps(&b[i]);
        __m128 c_data = _mm_load_ps(&c[i]);

        // Perform element-wise multiplication
        __m128 result = _mm_mul_ps(b_data, c_data);

        // Perform element-wise addition
        a_data = _mm_add_ps(a_data, result);

        // Store the result back to memory
        _mm_store_ps(&a[i], a_data);
    }
}
#else
#define NAME "not_vectorized"
void calculate_sum_and_mult(float* a, float* b, float* c, size_t size) {
    for(size_t i = 0; i < size; i++) {
        a[i] += b[i] * c[i];
    }
}
#endif

void benchmark(size_t repetitions) {
    float a[VECTOR_SIZE], b[VECTOR_SIZE], c[VECTOR_SIZE];

    for(size_t i = 0; i < repetitions; i++) {
        calculate_sum_and_mult(a, b, c, VECTOR_SIZE);
    }
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Usage: %s <repetitions>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t repetitions = atoi(argv[1]);

    double start_time = omp_get_wtime();

    benchmark(repetitions);

    double end_time = omp_get_wtime();
    double exc_time = end_time - start_time;

    printf("time: %lf\n", exc_time);

    add_time(NAME, 0, exc_time);

    return EXIT_SUCCESS;
}