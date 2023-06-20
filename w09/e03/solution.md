- Investigate the given code excerpt. Can this code be safely parallelized manually? Can this code be safely parallelized by the compiler?
```c
void copy(double* x, double* y) {
    for(int i = 0; i < 1024; i++) {
        x[i] = y[i];
    }
}
```

This example can easily be parallelized by the compiler by using vectorization, manually it is also easy to parallelize.
This is because there is no dependance in this loop.
If we would compile this code with `-O3` it would vectorize this loop. With omp we could use either the `omp parallel for` pragma or we could use `omp simd` pragma to either make a parallel loop or a vectorized loop.


- Normalize the following loop nest:
```c
for (int i=4; i<=N; i+=9) {
    for (int j=0; j<=N; j+=5) {
        A[i] = 0;
    }
}
```

First of all we can remove the inner loop, because that loop does not do anything, because j is never used:
```c
for (int i=4; i<=N; i+=9) {
        A[i] = 0;
}
```

Now we only need to normalize the 1 loop anymore.
For that we first decrease our starting value so it is 0 and apply that to every usage.

```c
for (int i=0; i + 4<=N; i+=9) {
        A[i + 4] = 0;
}
```

Now we want to have our `i` to only increase every iteration by 1, so we need to multiply our i by 9.

```c
for (int i=0; 9 * i + 4<=N; i++) {
        A[(9 * i) + 4] = 0;
}
```

Now we can also change the constant N, so we do not need to always calculate the 9 * i + 4:

```c
int n = (N - 4) / 9;
for (int i=0; i<=n; i++) {
        A[(9 * i) + 4] = 0;
}
```

This is now our final normalized loop.


- Does the following code excerpt hold any dependencies? If not, how would you parallelize it? If yes, what are the distance and direction vectors?
```c
for(int i = 1; i < N; i++) {
    for(int j = 1; j < M; j++) {
        for(int k = 1; k < L; k++) {
            a[i+1][j][k-1] = a[i][j][k] + 5;
        }
    }
}
```

The distance vectors looks like this: (1, 0, -1)
From this vector we can now derive the direction vector: (<, =, >)

But we can still parallelize one of those loops.
Because the j loop has no depandance we can only parallelize that loop. So we can use the `omp parallel for` pragma on the j loop as follows:

```c
for(int i = 1; i < N; i++) {
    #pragma omp parallel for
    for(int j = 1; j < M; j++) {
        for(int k = 1; k < L; k++) {
            a[i+1][j][k-1] = a[i][j][k] + 5;
        }
    }
}
```
