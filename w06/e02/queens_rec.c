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

int solve_queen_problem_rec(size_t n, size_t row, position* queens, size_t nq) {
    if(row > n) return 0;

    if(nq == n) {
        return 1;
    }

    int solutions = 0;
    for(size_t x = 0; x < n; x++) {
        position p = (position){ x, row };
        if(!is_position_attacked_by_queens(p, queens, nq)) {
            queens[nq] = p;
            solutions += solve_queen_problem_rec(n, row + 1, queens, nq + 1);
        }
    }

    return solutions;
}

int solve_queen_problem(size_t n) {
    position* queens = malloc(n * sizeof(position));
    for(size_t i = 0; i < n; i++) {
        queens[i] = (position){ 0, 0 };
    }

    size_t nq = 0;

    int solutions = solve_queen_problem_rec(n, 0, queens, nq);

    free(queens);

    return solutions;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <n-queens>\n", argv[0]);
        return 1;
    }

    size_t n = (size_t)atoi(argv[1]);

    int solutions = solve_queen_problem(n);

    printf("Solutions: %d\n", solutions);

    return 0;
}