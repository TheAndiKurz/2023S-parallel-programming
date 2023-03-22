#include <stdio.h>
#include <stdlib.h>

#define N 2

int main() {

    int32_t a[N][N], b[N][N], c[N][N] = {0};

    for(size_t i = 0; i < N; ++i) {
        for(size_t j = 0; j < N; ++j) {
            c[i][j] = a[i][j] * b[i][j];
        }
    }
}
