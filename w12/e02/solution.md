### Description

For each loop iteration instructions such as compare and add operations have to be performed. If the number of executions is sufficiently large this can have an impact on the performance of the program. Investigate the following given code examples along with their task and, for each example, study why the transformation may or may not be beneficial. \
Furthermore, for each example, you are asked to compare the performance counters of the original and the transformed code. Therefore, you should create a small test program for each configuration, compile it with `gcc` using `-O3`, and profile it with `perf` on LCC2.
Note that if not stated otherwise, variables and array elements are of type `int`.

### Tasks

- Apply loop unrolling, increase the workload per iteration. \
Note that you can assume that `N` is odd.
```C
for (int i = 0; i < N - 1; ++i) {
    a[i] = b[i] + b[i + 1];
}
```

- Apply loop-invariant code motion, reduce the number of function calls.\
`a` is of type `double *`
```C
for (int i = 0; i < N; ++i) {
    a[i] *= hypot(0.3, 0.4);
}
```

We can just move `hypot(0.3, 0.4)` out of the loop as it is loop-invariant:
```C
double hyp = hypot(0.3, 0.4);
for (int i = 0; i < N; ++i) {
    a[i] *= hyp;
}
```
The number of function calls get reduced from `N` to `1`.

- Apply loop unswitching, eliminate the if clause inside the loop.
```C
for (int i = 0; i < N; ++i) {
    if (N % 2) {
        a[i] = b[i] + 5;
    } else {
        a[i] = c[i] + 5;
    }
}
```

The if clause can be eliminated by moving it out of the loop, as it only depends on `N`:
```C
if (N % 2) {
    for (int i = 0; i < N; ++i) {
        a[i] = b[i] + 5;
    }
} else {
    for (int i = 0; i < N; ++i) {
        a[i] = c[i] + 5;
    }
}
```
This could even be done in less code by using an additional variable:
```C
int *arr = (N % 2) ? b : c;
for (int i = 0; i < N; ++i) {
    a[i] = arr[i] + 5;
}
```
The loop unsitching reduces the number of comparisons from `N` to `1`.

- Apply loop fission/distribution, reduce the number of instructions per iteration. \
Does this transformation have an impact on the number of cache misses?
```C
for (int i = 0; i < N; ++i) {
    sum_a += a[i];
    sum_b += b[i];
    sum_c += c[i];
}
```

The loop can be split into three loops, each with only one instruction per iteration:
```C
for (int i = 0; i < N; ++i) {
    sum_a += a[i];
}
for (int i = 0; i < N; ++i) {
    sum_b += b[i];
}
for (int i = 0; i < N; ++i) {
    sum_c += c[i];
}
```
This tranformation indeed impacts the number of cache misses, as only the data of one array accessed sequentially and then the next one. This should be better then the original, as, for big arrays, the cache will be filled only with data from one array which is easier to predict.
On the other hand the number of comparisons is increased from `N` to `3 * N`.


- Apply loop peeling and loop fusion/combination, combine the snippet into a single loop. \
Note that `N` is larger than `0`.
```C
int min = a[0];
for (int i = 1; i < N; ++i) {
    min = (a[i] < min) ? a[i] : min;
}
for (int i = 0; i < N; ++i) {
    sum += a[i];
}
```

The first iteration of the second loop must be done outside of the loop, as `min` is not initialized yet. This is called loop peeling. Then the two loops can be combined into one:
```C
int min = a[0];
int sum = a[0];
for (int i = 1; i < N; ++i) {
    min = (a[i] < min) ? a[i] : min;
    sum += a[i];
}
```


- Apply loop splitting, reduce the number of compare instructions per iteration.
```C
for (int i = 0; i < N; ++i) {
    if (i % 2) {
        a[i] = b[i] + 4;
    } else {
        a[i] = c[i] + 5;
    }
}
```

The loop can be split into two loops, one for the even and one for the odd indices:
```C
for (int i = 0; i < N; i += 2) {
    a[i] = c[i] + 5;
}
for (int i = 1; i < N; i += 2) {
    a[i] = b[i] + 4;
}
```
The number of comparisons is reduced from `N` (loop condition) + `N` (if clause) `= 2N` to `2 * N / 2 = N` (loop condition).

These loops could even be combined into one loop, as the if clause is not needed anymore:
```C
a[0] = c[0] + 5;
for (int i = 0; i < N-1; i += 2) {
    a[i] = c[i] + 5;
    a[i + 1] = b[i + 1] + 4;
}
```

- Apply loop tiling, when addresses are accessed multiple times it is beneficial to work in blocks of the same length as the cache line size. Add loops so that the read and write accesses are limited to one block at a time.\
 You can assume that a macro `BLOCK_SIZE`, which is defined in some boilerplate code, defines a suitable block size for tiling (e.g., `#define BLOCK_SIZE 64 / sizeof(double)`). \
`a`, `b`, and `c` are of type `double`
```C
for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
        for (int k = 0; k < N; ++k) {
            c[i][j] = a[i][k] * b[k][j];
        }
    }
}
```
The innermost loop seems to be irrelevant, as c[][] will be overwritten each iteration. Thus the loop can be replaced by the last iteration:
```C
for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
        c[i][j] = a[i][N - 1] * b[N - 1][j];
    }
}
```
Now we can apply loop tiling to the two outer loops:
```C
for (int ic = 0; i < N; ic += BLOCK_SIZE) {
    for (int jc = 0; j < N; jc += BLOCK_SIZE) {
        int i_lim = (ic + BLOCK_SIZE < N) ? ic + BLOCK_SIZE : N;
        int j_lim = (jc + BLOCK_SIZE < N) ? jc + BLOCK_SIZE : N;
        for (int i = ic; i < i_lim; ++i) {
            for (int j = jc; j < j_lim; ++j) {
                c[i][j] = a[i][N - 1] * b[N - 1][j];
            }
        }
    }
}
```


## General Notes

All the material required by the tasks above (e.g., code, figures, text, etc...) must be part of the solution that is handed in. Your experiments should be reproducible and comparable to your measurements using the solution materials that you hand in.

**Every** member of your group must be able to explain the given problem, your solution, and possible findings. You may also need to answer detailed questions about any of these aspects.