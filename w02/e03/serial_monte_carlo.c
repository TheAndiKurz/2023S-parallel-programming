#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

double rand_double(unsigned *seed)
{
    return (double)rand_r(seed) / (double)RAND_MAX;
}

double monte_carlo(size_t n)
{
    size_t inside = 0;
    unsigned seed = time(NULL);

    for (size_t i = 0; i < n; i++)
    {
        double x = rand_double(&seed), y = rand_double(&seed);

        if (x * x + y * y <= 1)
        {
            inside++;
        }
    }

    return (double)(4 * inside) / (double)n;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <number-of-points>\n", argv[0]);
        return 1;
    }

    double startTime = omp_get_wtime();

    double pi_aprx = monte_carlo(atoi(argv[1]));

    double endTime = omp_get_wtime();

    printf("Monte Carlo Pi: %lf\n", pi_aprx);
    printf("time: %lf\n", endTime - startTime);

    return 0;
}