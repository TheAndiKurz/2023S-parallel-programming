#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

double rand_double(unsigned *seed)
{
    return (double)rand_r(seed) / (double)RAND_MAX;
}

size_t monte_carlo_thread(size_t n)
{
    unsigned seed = (unsigned)time(NULL) + omp_get_thread_num();

    size_t inside = 0;

    for (size_t i = 0; i < n; i++)
    {
        double x = rand_double(&seed);
        double y = rand_double(&seed);

        if (x * x + y * y <= 1)
        {
            inside++;
        }
    }

    return inside;
}

double monte_carlo(const size_t n_threads, const size_t n)
{

    size_t inside = 0;
#pragma omp parallel num_threads(n_threads)
    {
        size_t ID = (size_t)omp_get_thread_num();

        size_t thread_n = n / n_threads;

        if (ID < (n % n_threads))
            thread_n++;

        inside += monte_carlo_thread(thread_n);
    }

    return (double)(4 * inside) / (double)n;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "usage: %s <number-of-threads> <number-of-points>\n", argv[0]);
        return 1;
    }

    int threads = atoi(argv[1]);
    int n = atoi(argv[2]);

    double startTime = omp_get_wtime();

    double pi_aprx = monte_carlo(threads, n);

    double endTime = omp_get_wtime();

    double exc_time = endTime - startTime;

    printf("Monte Carlo Pi: %lf\n", pi_aprx);
    printf("time: %lf\n", exc_time);

    FILE *f = fopen("values.csv", "a+");

    fprintf(f, "Parallel %d, %lf, %lf\n", threads, exc_time, pi_aprx);

    fclose(f);

    return 0;
}