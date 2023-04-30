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
#define VERSION_TEXT "array stack"
uint64_t delannoy(int n, int m){
    //check if the argument is 0
    if (n == 0 || m == 0)
    {
        return 1;
    }

    uint64_t delannoy[n + 1][m + 1];

    //initialize the first column to 1
    for (int i = 0; i <= n; i++)
    {
        delannoy[i][0] = 1;
    }
    //initialize the first row  to 1
    for (int i = 0; i <= m; i++)
    {
        delannoy[0][i] = 1;
    }
    //calculate the Delannoy numbers for the rest of the grid
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j ++)
        {
            delannoy[i][j] = delannoy[i - 1][j] + delannoy[i - 1][j - 1] + delannoy[i][j - 1];
        }
    }
    return delannoy[n][m];
}
#elif VERSION == 2
#define VERSION_TEXT "array heap"
uint64_t delannoy(int m, int n){
    //check if the argument is 0
    if (n == 0 || m == 0)
    {
        return 1;
    }
    //create a 2D array to store the Delannoy numbers
    uint64_t **delannoy = malloc(sizeof(uint64_t*)*(n+1));

    //initialize the first column to 1
    for (int i = 0; i <= n; i++)
    {
        delannoy[i] = malloc(sizeof(uint64_t)*(m+1));
        delannoy[i][0] = 1;
    }
    //initialize the first row  to 1
    for (int i = 0; i <= m; i++)
    {
        delannoy[0][i] = 1;
    }
    //calculate the Delannoy numbers for the rest of the grid
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j ++)
        {
            delannoy[i][j] = delannoy[i - 1][j] + delannoy[i - 1][j - 1] + delannoy[i][j - 1];
        }
    }

    uint64_t del = delannoy[n][m];  
    free(delannoy);
    return del;
}
#elif VERSION == 3
#define VERSION_TEXT "rows"
uint64_t delannoy(int m, int n){
    //check if the argument is 0
    if (n == 0 || m == 0)
    {
        return 1;
    }
    //create a 2D array to store the Delannoy numbers
    uint64_t delannoy_a[m + 1];
    uint64_t delannoy_b[m + 1];

    //initialize the first row to 1
    for (int i = 0; i <= m; i++)
    {
        delannoy_a[i] = 1;
    }
    delannoy_b[0] = 1;
    
    uint64_t* top = delannoy_a;
    uint64_t* curr = delannoy_b;
    uint64_t* temp;

    //calculate the Delannoy numbers for the rest of the grid
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            curr[j] = top[j] + top[j - 1] + curr[j - 1];
        }
        temp = top;
        top = curr;
        curr = temp;
    }
    return top[m];
}
#elif VERSION == 4
#define VERSION_TEXT "shrinking rows"
uint64_t delannoy(int m, int n){
    //check if the argument is 0
    if (n == 0 || m == 0)
    {
        return 1;
    }
    //create a 2D array to store the Delannoy numbers
    uint64_t delannoy_a[m + 1];
    uint64_t delannoy_b[m + 1];

    //initialize the first row to 1
    for (int i = 0; i <= m; i++)
    {
        delannoy_a[i] = 1;
    }
    delannoy_b[0] = 1;
    
    uint64_t* top = delannoy_a;
    uint64_t* curr = delannoy_b;
    uint64_t* temp;

    //calculate the Delannoy numbers for the rest of the grid
    for (int i = 1; i <= n; i++)
    {
        // the first entry can be computed without the left entry, as its on the diagonal.
        curr[i] = top[i] + top[i - 1] + top[i];
        for (int j = i+1; j <= m; j++)
        {
            curr[j] = top[j] + top[j - 1] + curr[j - 1];
        }
        temp = top;
        top = curr;
        curr = temp;
    }
    return top[m];
}
#elif VERSION == 5
#define VERSION_TEXT "recursive"
//function calculating delannoy numbers recursivly
uint64_t delannoy(int m, int n){
    if(n == 0 || m == 0) return 1;
    return delannoy(m-1, n) + delannoy(m-1, n-1) + delannoy(m, n-1);
}
#endif /* if VERSION */

void print_usage(){
    printf("Invalid arguments. usage:\n ./delannoy_number_par_nrecursive <grid size> [-w]\n");
    printf("  -w: write the number of threads (here 1) to the csv file (by default the grid size is written).");
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

    uint64_t del = delannoy(n,n);

    double endTime = omp_get_wtime();
    double exc_time = endTime - startTime;

    char msg[512];
    if (write_threads) {
        sprintf(msg, "seqential %s - n=%d", VERSION_TEXT, n);
        add_time(msg, 1, exc_time);
    } else {
        sprintf(msg, "seqential %s", VERSION_TEXT);
        add_time(msg, n, exc_time);
    }

    //print out the Delannoy number for the given grid size
    printf("The Delannoy number for a %dx%d grid is %llu, in %lfs.\n", n, n, del, exc_time);
    return 0;
}

