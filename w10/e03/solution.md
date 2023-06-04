```c
for (int i = 0; i < 4; ++i) {
    for (int j = 1; j < 4; ++j) {
        a[i + 2][j - 1] = b * a[i][j] + 4;
    }
}
```

Iteration vectors:
[0,1]; [0,2]; [0,3];
[1,1]; [1,2]; [1,3];
[2,1]; [2,2]; [2,3];
[2,1]; [2,2]; [2,3];
[3,1]; [3,2]; [3,3];

Distance Vector: (2,-1)
Direction Vector: (<,>)
These vectors do not change throughout the whole iteration space.

```c
for (int i = 0; i < 4; ++i) {
#pragma omp parallel for // NOTE: parallelize inner loop as dependency is carried by the outer dependence
    for (int j = 1; j < 4; ++j) {
        a[i + 2][j - 1] = b * a[i][j] + 4;
    }
}
```
