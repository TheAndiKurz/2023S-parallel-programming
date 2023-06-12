#include "vec3.h"

vec3 vec3_add(vec3 a, vec3 b) {
    return (vec3){ a.x + b.x, a.y + b.y, a.z + b.z };
}

vec3 vec3_sub(vec3 a, vec3 b) {
    return (vec3){ a.x - b.x, a.y - b.y, a.z - b.z };
}

vec3 vec3_mul(vec3 a, double b) {
    return (vec3){ a.x * b, a.y * b, a.z * b };
}

vec3 vec3_div(vec3 a, double b) {
    return (vec3){ a.x / b, a.y / b, a.z / b };
}

double vec3_dot(vec3 a, vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double vec3_len(vec3 a) {
    return sqrt(vec3_dot(a, a));
}

// fast inverse square root from quake 3, just that it is double precision
double Qd_rsqrt(double num, int iters) {
    double x2 = num * 0.5;
    double y = num;

    long i = *(long*)&y;
    i = 0x5fe6ec85e7de30daL - (i >> 1);
    y = *(double*)&i;

    // newton iteration for better accuracy
    for(int it = 0; it < iters; it++) {
        y *= (1.5 - (x2 * y * y));
    }

    return y;
}

vec3 vec3_normalize(vec3 a) {
    double inv_len = Qd_rsqrt(vec3_dot(a, a), 4);

    return vec3_mul(a, inv_len);
}