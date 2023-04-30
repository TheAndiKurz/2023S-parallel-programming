#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../tools/time/time.h"

#ifndef VERSION
    #define VERSION 1
#endif /* ifndef VERSION */ 

#if VERSION == 1
#define VERSION_TEXT "naive recursive"
//function calculating delannoy numbers recursivly
uint64_t delannoy(int m, int n){
    if(n == 0 || m == 0) return 1;

    uint64_t t1, t2, t3; 
  
    #pragma omp task shared(t1)
        t1 = delannoy(m-1, n);
    #pragma omp task shared(t2)
        t2 = delannoy(m-1, n-1);
    #pragma omp task shared(t3)
        t3 = delannoy(m, n-1);

    #pragma omp taskwait
    return t1 + t2 + t3;
}
#elif VERSION == 2
#define VERSION_TEXT "recursive "
//function calculating delannoy numbers recursivly
uint64_t delannoy_rec(int m, int n){
    if(n == 0 || m == 0) return 1;

    return delannoy_rec(m-1, n)
         + delannoy_rec(m-1, n-1)
         + delannoy_rec(m, n-1);
}
uint64_t delannoy_helper(int m, int n, int d){
    if(n == 0 || m == 0) return 1;

    if (d <= MAX_NUM_TASKS) {
      uint64_t t1, t2, t3; 
      #pragma omp task shared(t1)
          t1 = delannoy_helper(m-1, n, d*3);
      #pragma omp task shared(t2)
          t2 = delannoy_helper(m-1, n-1, d*3);
      #pragma omp task shared(t3)
          t3 = delannoy_helper(m, n-1, d*3);
      #pragma omp taskwait
      return t1 + t2 + t3;
    } else {
          return delannoy_rec(m-1, n)
               + delannoy_rec(m-1, n-1)
               + delannoy_rec(m, n-1);
    }
}
uint64_t delannoy(int m, int n){
    return delannoy_helper(m,n,1);
}
#endif /* if VERSION */

int main(int argc, char *argv[])
{
    //check if the number of arguments is correct
    if (argc != 2 || (argc > 2 && argv[1][0] == '-'))
    {
        printf("Invalid arguments. usage:\n ./delannoy_number_seq <grid size>\n or\n ./delannoy_number_seq -t <grid size> <max. number of tasks>\n");
        return 1;
    }
    int n = 0;
    int t = 0;
    //if argument '-s' is given 
    if (argv[1][0] == '-' && argv[1][1] == 't'){
        n = atoi(argv[2]);
        t = atoi(argv[3]);
        if ((m <= 0 && argv[2][0] != '0') || (n <= 0 && argv[2][0] != '0'))
        {
        printf("Invalid arguments. usage:\n ./delannoy_number_seq <grid size>\n or\n ./delannoy_number_seq -t <grid size> <max. number of tasks>\n");
            return 1;
        }
    } else {
        //convert the argument to an integer
        n = atoi(argv[1]);
        //check if the argument is a positive integer
        if (n <= 0 && argv[1][0] != '0')
        {
        printf("Invalid arguments. usage:\n ./delannoy_number_seq <grid size>\n or\n ./delannoy_number_seq -t <grid size> <max. number of tasks>\n");
            return 1;
        }
    }

    double startTime = omp_get_wtime();
    uint64_t del = 0;
    #pragma omp parallel
    {
        #pragma omp single
#if VERSION==1
        del = delannoy(n,n,t);
#else 
        del = delannoy(n,n);
#endif
    }

    double endTime = omp_get_wtime();
    double exc_time = endTime - startTime;

    char msg[512];
#ifdef WRITE_NUM_THREADS 
    sprintf(msg, "parallel - %s %d tasks", VERSION_TEXT, MAX_NUM_TASKS);
    add_time(msg, omp_get_max_threads(), exc_time);
#else 
    #ifdef MAX_NUM_TASKS
    sprintf(msg, "parallel - %s %d tasks/%d threads", VERSION_TEXT, MAX_NUM_TASKS, omp_get_max_threads());
    #else 
    sprintf(msg, "parallel - %s/%d threads", VERSION_TEXT, omp_get_max_threads());
    #endif /*ifdef MAX_NUM_THREADS */

    add_time(msg, n, exc_time);
#endif /*ifdef WRITE_NUM_THREADS */

    //print out the Delannoy number for the given grid size
    printf("The Delannoy number for a %dx%d grid is %llu, in %lfs.\n", m, n, del, exc_time);
    return 0;
}

