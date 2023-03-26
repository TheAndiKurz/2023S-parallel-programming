#include <omp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

double rand_double(unsigned* seed) {
    return (double)rand_r(seed) / (double)RAND_MAX;
}

void* monte_carlo_thread(void* args) {
    size_t n = *((size_t*)args);

    unsigned seed = (unsigned)pthread_self();

    size_t inside = 0;

    for(size_t i = 0; i < n; i++) {
        double x = rand_double(&seed);
        double y = rand_double(&seed);

        if(x * x + y * y <= 1) {
            inside++;
        }
    }

    return (void*)inside;
}

double monte_carlo(const size_t n_threads, const size_t n) {
    pthread_t threads[n_threads];
    size_t args[n_threads];

    // iterations each thread has to calculate
    size_t n_thread = n / n_threads;

    // this is needed when not every thread can have the same
    size_t n_diff = n % n_threads;

    for(size_t i = 0; i < n_threads; i++) {
        args[i] = n_thread;

        if(i < n_diff) {
            args[i]++;
        }

        // create and start the thread
        pthread_create(threads + i, NULL, monte_carlo_thread, (void*)(args + i));
    }

    // number of dots generated in the unit circle
    size_t inside = 0;

    for(size_t i = 0; i < n_threads; i++) {
        void* ret;
        pthread_join(threads[i], &ret);

        inside += (size_t)ret;
    }

    return (double)(4 * inside) / (double)n;
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
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

    FILE* f = fopen("values.csv", "a+");

    fprintf(f, "Parallel %d, %lf, %lf\n", threads, exc_time, pi_aprx);

    fclose(f);

    return 0;
}