#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../tools/time/time.h"

//function calculating delannoy numbers recursivly
uint64_t delannoy(int m, int n){
    if(n == 0 || m == 0) return 1;

    uint64_t t1, t2, t3; 
  
    #pragma omp task shared(t1) firstprivate(m,n) 
        t1 = delannoy(m-1, n);
    #pragma omp task shared(t2) firstprivate(m,n)
        t2 = delannoy(m-1, n-1);
    #pragma omp task shared(t3) firstprivate(m,n)
        t3 = delannoy(m, n-1);

    #pragma omp taskwait
    return t1 + t2 + t3;
}
void print_usage(){
    printf("Invalid arguments. usage:\n ./delannoy_number_par_nrecursive <grid size> [-w]\n");
    return;
}

int main(int argc, char *argv[])
{
    //check if the number of arguments is correct
    if (argc < 2 || argc > 3)
    {
        print_usage();
        return 1;
    }
    int n = 0;
    //convert the argument to an integer
    n = atoi(argv[1]);
    //check if the argument is a positive integer
    if (n <= 0 && argv[1][0] != '0')
    {
        print_usage();
        return 1;
    }
    bool write_threads = false;
    if (argc == 3) {
        if (argv[argc-1][0] != '-' || argv[argc-1][1] != 'w') {
            print_usage();
            return 1;
        }
        write_threads = true;
    }

    double startTime = omp_get_wtime();
    uint64_t del = 0;
    #pragma omp parallel
    {
        #pragma omp single
        del = delannoy(n,n);
    }

    double endTime = omp_get_wtime();
    double exc_time = endTime - startTime;

    char msg[512];

    if (write_threads){
        sprintf(msg, "naive parallel recursive - n=%d", n);
        add_time(msg, omp_get_max_threads(), exc_time);
    } else {
        sprintf(msg, "naive parallel recursive - %d threads", omp_get_max_threads());
        add_time(msg, n, exc_time);
    }

    //print out the Delannoy number for the given grid size
    printf("The Delannoy number for a %dx%d grid is %llu, in %lfs.\n", n, n, del, exc_time);
    return 0;
}

