#pragma once

#include <math.h>

struct vec3 {
    double x, y, z;
};
typedef struct vec3 vec3;

vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_sub(vec3 a, vec3 b);
vec3 vec3_mul(vec3 a, double b);
vec3 vec3_div(vec3 a, double b);

double vec3_dot(vec3 a, vec3 b);
double vec3_len(vec3 a);

vec3 vec3_normalize(vec3 a);