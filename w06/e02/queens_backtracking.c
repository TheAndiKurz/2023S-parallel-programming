#include "../../tools/time/time.h"
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct position {
    size_t x;
    size_t y;
};
typedef struct position position;

bool is_position_attacked_by_queen(position p, position q) {
    return p.x == q.x ||             // same row
           p.y == q.y ||             // same column
           p.x - p.y == q.x - q.y || // diagonal down
           p.x + p.y == q.x + q.y;   // diagonal up
}

bool is_position_attacked_by_queens(position p, position* q, size_t nq) {
    for(size_t i = 0; i < nq; i++) {
        if(is_position_attacked_by_queen(p, q[i])) {
            return true;
        }
    }
    return false;
}

void print_queens(position* queens, size_t nq) {
    for(size_t i = 0; i < nq; i++) {
        printf("(%lu, %lu) ", queens[i].x, queens[i].y);
    }
    printf("\n");
}

size_t solve_queen_problem_rec(size_t n, size_t row, position* queens) {

    if(row == n) {
        return 1;
    }

    if(row > n) {
        return 0;
    }

    size_t solutions = 0;
    for(size_t x = 0; x < n; x++) {
        position p = (position){ x, row };
        if(!is_position_attacked_by_queens(p, queens, row)) {
            queens[row] = p;
            solutions += solve_queen_problem_rec(n, row + 1, queens);
        }
    }

    return solutions;
}

int solve_queen_problem(size_t n) {
    size_t solutions = 0;
#ifdef PARALLEL
#pragma omp parallel for reduction(+ : solutions)
#endif
    for(size_t x = 0; x < n; x++) {
        position p = (position){ x, 0 };
        position* queens = malloc(n * sizeof(position));
        queens[0] = p;

        solutions += solve_queen_problem_rec(n, 1, queens);

        free(queens);
    }

    return solutions;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <n-queens>\n", argv[0]);
        return 1;
    }

    size_t n = (size_t)atoi(argv[1]);

    double startTime = omp_get_wtime();

    size_t solutions = solve_queen_problem(n);

    double endTime = omp_get_wtime();
    double exc_time = endTime - startTime;
    printf("time: %lf\n", exc_time);
    printf("Solution: %lu\n", solutions);

    char name[TIME_CELL_LEN];
    snprintf(name, TIME_CELL_LEN, "number-of-queens=%03lu", n);

#ifdef PARALLEL
    size_t threads = omp_get_max_threads();
#else
    size_t threads = 0;
#endif
    add_time_value(name, threads, exc_time, (double)solutions);

    return 0;
}