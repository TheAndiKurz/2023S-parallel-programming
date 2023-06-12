#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "vec3.h"

#define SIZE_UNIVERSE_X 100
#define SIZE_UNIVERSE_Y 100
#define SIZE_UNIVERSE_Z 100

#define TIME_STEP 1

#define GRAVITATION_CONSTANT -1

typedef struct {
    vec3 pos;
    vec3 velocity;
    vec3 force;
    double mass;
} particle;

void particle_init(particle* p, vec3 pos, double mass) {
    p->pos = pos;
    p->mass = mass;
    p->velocity = (vec3){ 0, 0, 0 };
    p->force = (vec3){ 0, 0, 0 };
}

typedef struct {
    size_t n;
    particle* particles;
} universe;

void universe_init(universe* u, size_t n) {
    u->n = n;
    u->particles = malloc(n * sizeof(particle));
}

void universe_destroy(universe* u) {
    free(u->particles);
}

void universe_insert_particle(universe* u, size_t index, particle p) {
    u->particles[index] = p;
}

void random_universe(universe* u, size_t n) {
    universe_init(u, n);

    for(size_t i = 0; i < n; i++) {
        vec3 pos =
            (vec3){ rand() % SIZE_UNIVERSE_X, rand() % SIZE_UNIVERSE_Y, rand() % SIZE_UNIVERSE_Z };

        pos.x = fabs(pos.x);
        pos.y = fabs(pos.y);
        pos.z = fabs(pos.z);

        // generate a double between 10000 and 100000
        double mass = rand() / (double)RAND_MAX * 90000 + 10000;
        particle p;
        particle_init(&p, pos, mass);
        universe_insert_particle(u, i, p);
    }
}

void particle_calculate_force(particle* p, universe* u) {
    for(size_t i = 0; i < u->n; i++) {
        particle* q = &u->particles[i];
        if(p == q) {
            continue;
        }

        vec3 diff = vec3_sub(p->pos, q->pos);
        double dist_sq = vec3_dot(diff, diff);
        double force = GRAVITATION_CONSTANT * (p->mass * q->mass) / (dist_sq);
        vec3 dir = vec3_normalize(diff);

        vec3 f = vec3_mul(dir, force);
        p->force = vec3_add(p->force, f);
    }
}

void particle_apply_force(particle* p) {
    vec3 acceleration = vec3_div(p->force, p->mass);

    p->velocity = vec3_add(p->velocity, vec3_mul(acceleration, TIME_STEP));
    p->pos = vec3_add(p->pos, vec3_mul(p->velocity, TIME_STEP));
}

void universe_calculate_step(universe* u) {
#ifdef PARALLEL
#pragma omp for
#endif
    for(size_t i = 0; i < u->n; i++) {
        particle_calculate_force(&(u->particles[i]), u);
    }
#ifdef PARALLEL
#pragma omp for
#endif
    for(size_t i = 0; i < u->n; i++) {
        particle_apply_force(&(u->particles[i]));
    }
}

void write_gnuplot(FILE* f, universe* u) {
    for(size_t i = 0; i < u->n; i++) {
        particle* p = &u->particles[i];
        fprintf(f, "%f %f %f\n", p->pos.x, p->pos.y, p->pos.z);
    }

    fprintf(f, "\n\n");
}

void nBodySimulation(size_t n_particles, size_t n_steps) {
    universe u;
    random_universe(&u, n_particles);

    FILE* data_file = fopen("data.dat", "w");

    write_gnuplot(data_file, &u);

#ifdef PARALLEL
#pragma omp parallel
#endif
    for(size_t i = 0; i < n_steps; i++) {
        universe_calculate_step(&u);
        write_gnuplot(data_file, &u);
    }

    fclose(data_file);

    universe_destroy(&u);
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage: %s <number-of-particles> <number-of-steps>\n", argv[0]);
        exit(1);
    }

    size_t n_particles = (size_t)strtoul(argv[1], NULL, 10);
    size_t n_steps = (size_t)strtoul(argv[2], NULL, 10);

    nBodySimulation(n_particles, n_steps);

    return 0;
}