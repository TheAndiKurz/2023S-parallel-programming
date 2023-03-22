#include <stdio.h>
#include <stdlib.h>

int main() {
    const int n = 1000;

    int a[n][n], b[n][n], c[n][n];
    for(size_t j = 0; j < n; ++j) {
        for(size_t i = 0; i < n; ++i) {
            c[i][j] = a[i][j] * b[i][j];
        }
    }
}
