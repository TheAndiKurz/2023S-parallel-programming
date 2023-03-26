#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10 * 1000

int32_t** create_matrix(size_t size) {
    int32_t* array = malloc(size * size * sizeof(int32_t));
    int32_t** matrix = malloc(size * sizeof(int32_t*));

    for(size_t i = 0; i < size; ++i) {
        matrix[i] = array + i * size;
    }

    return matrix;
}

void free_matrix(int32_t** matrix) {
    free(*matrix);
    free(matrix);
}

int main() {
    int32_t** a = create_matrix(N);
    int32_t** b = create_matrix(N);
    int32_t** c = create_matrix(N);

    size_t n = N;
    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < n; ++j) {
            c[i][j] = a[i][j] * b[i][j];
        }
    }

    free_matrix(a);
    free_matrix(b);
    free_matrix(c);
}
