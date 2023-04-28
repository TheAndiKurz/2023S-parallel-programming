#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../tools/time/time.h"

//function calculating delannoy numbers recursivly
uint64_t delannoy_rec(int m, int n){
    if(n == 0 || m == 0) return 1;

    return delannoy_rec(m-1, n)
         + delannoy_rec(m-1, n-1)
         + delannoy_rec(m, n-1);
}
uint64_t delannoy_helper(int m, int n, int d, int n_tasks){
    if(n == 0 || m == 0) return 1;

    if (d <= n_tasks) {
        uint64_t t1, t2, t3; 
        #pragma omp task shared(t1) firstprivate(m,n,d,n_tasks)
            t1 = delannoy_helper(m-1, n, d*3, n_tasks);
        #pragma omp task shared(t2) firstprivate(m,n,d,n_tasks) 
            t2 = delannoy_helper(m-1, n-1, d*3, n_tasks);
        #pragma omp task shared(t3) firstprivate(m,n,d,n_tasks) 
            t3 = delannoy_helper(m, n-1, d*3, n_tasks);
        #pragma omp taskwait
        return t1 + t2 + t3;
    } else {
        return delannoy_rec(m-1, n)
             + delannoy_rec(m-1, n-1)
             + delannoy_rec(m, n-1);
    }
}
uint64_t delannoy(int m, int n, int n_tasks){
    return delannoy_helper(m,n,1,n_tasks);
}

void print_usage(){
    printf("Invalid arguments. usage:\n");
    printf("  ./delannoy_number_par_recursive <grid size> [-t <number of tasks>] [-w <name>]\n");
    printf("  -t: specify the maximum number of tasks to spawn\n");
    printf("  -w: write the parameter specified by <name> to the csv file\n      name can be one of 's' (size of grid, default), 't' (number of tasks) or 'n' (number of threads)\n");
    return;
}

int main(int argc, char *argv[])
{
    /* start input handling  */
    //check if the number of arguments is correct
    if (argc < 2 || argc > 6)
    {
        print_usage();
        return 1;
    }
    int n = 0;
    int n_tasks = 0;
    //convert size
    n = atoi(argv[1]);
    //check if the argument is a positive integer
    if (n <= 0 && argv[1][0] != '0')
    {
        print_usage();
        return 1;
    }
    //set to n by default
    int output_parameter_value = n;
    char output_parameter = '\0';
    //case both flags set:
    if (argc == 6) {
        if (argv[2][0] != '-' || argv[2][1] != 't' || argv[4][0] != '-' || argv[4][1] != 'w') {
            print_usage();
            return 1;
        }
        n_tasks = atoi(argv[3]);
        if (argv[5][0] == 't') {
            output_parameter_value = n_tasks;
            output_parameter = 't';
        } else if (argv[5][0] == 'n') {
            output_parameter_value = omp_get_max_threads();
            output_parameter = 'n';
        }
    } else if (argc == 4) {
        if ((argv[2][0] != '-' || argv[2][1] != 't') && (argv[2][0] != '-' || argv[2][1] != 'w')) {
            print_usage();
            return 1;
        } 
        if (argv[2][1] == 't') {
            n_tasks = atoi(argv[3]);
        } else {
            if (argv[3][0] == 't') {
                output_parameter = n_tasks;
                output_parameter = 't';
            } else if (argv[3][0] == 'n') {
                output_parameter = omp_get_max_threads();
                output_parameter = 'n';
            }
        }
    }
    /* end input handling  */

    double startTime = omp_get_wtime();
    uint64_t del = 0;
    #pragma omp parallel
    {
        #pragma omp single
        del = delannoy(n,n,n_tasks);
    }

    double endTime = omp_get_wtime();
    double exc_time = endTime - startTime;

    char msg[512];
    
    if (output_parameter == 't') {
        sprintf(msg, "parallel recursive - n=%d/%d threads", n, omp_get_max_threads());
    } else if (output_parameter == 'n') {
        sprintf(msg, "parallel recursive - n=%d/%d tasks", n, n_tasks);
    } else {
        sprintf(msg, "parallel recursive - %d threads/%d tasks", omp_get_max_threads(), n_tasks);
    }
    add_time(msg, output_parameter_value, exc_time);

    //print out the Delannoy number for the given grid size
    printf("The Delannoy number for a %dx%d grid is %llu, in %lfs.\n", n, n, del, exc_time);
    return 0;
}

