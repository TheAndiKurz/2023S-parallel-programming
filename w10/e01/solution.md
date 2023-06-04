```c
for (int i=0; i < n-1; i++) {
    x[i] = (y[i] + x[i+1]) / 7; // S1
}
```

There exists a loop caried anti dependence (WAR) on x
distance vector: (0, 1)
direction vector: (=,<)

Anti dependencies can easily be fixed by variable renaming / copying of the datastructure.

```c
// NOTE: Assume double datatype.
const size_t MEM_SIZE = n * sizeof(double);
double* temp = malloc(MEM_SIZE);
memcpy(temp, x, MEM_SIZE);
#pragma omp parallel for
for (int i=0; i < n-1; i++) {
    x[i] = (y[i] + temp[i+1]) / 7; // S1
}
free(temp);
```
---------------------------------------------------------------------------------------------------
```c
for (int i=0; i < n; i++) {
    a = (x[i] + y[i]) / (i+1); // S1
    z[i] = a; // S2
}

f = sqrt(a + k);
```

There only exists an indirect dependence on the last known value of a which can be calculated easily.
S1:
    distance vector: (0, 0)
    direction vector: (=, =)

S2:
    distance vector: (0)
    direction vector: (=)

S2 d S2: 
    distance vector: (0) d (0, 0)
    direction vector: (=)
```c
for (int i=0; i < n; i++) {
    a = (x[i] + y[i]) / (i+1);
    z[i] = a; 
}

a = (x[n-1] + y[n-1]) / n);
f = sqrt(a + k); // NOTE: Dependant on the last sequential value of a.
```
---------------------------------------------------------------------------------------------------
```c
for (int i=0; i < n; i++) {
   x[i] = y[i] * 2 + b * i;
}


for (int i=0; i < n; i++) {
   y[i] = x[i]  + a / (i+1);
}
```

There are again no loop carried dependencies for each loop but just a race condition if parallelized
incorrectly (nowait). We can either parallelize both loops in one parallel region or we can merge the two loops.

```c
#pragma omp parallel
{

#pragma omp for
    for (int i=0; i < n; i++) {
        x[i] = y[i] * 2 + b * i;
    }

#pragma omp for
    for (int i=0; i < n; i++) {
        y[i] = x[i]  + a / (i+1);
    }
} // End of parallel region
```

```c
#pragme omp parallel for
for (int i=0; i < n; i++) { // NOTE: Loop has same iteration vectors therefore mergeable.
   x[i] = y[i] * 2 + b * i;
   y[i] = x[i]  + a / (i+1);
}
```
Due to the possibility of a race condition if the two for loops are parallelized incorrectly and the
possibility for less overhead caused by parallelization in addition to potentially better load ballancing,
I think it makes sense to merge these two for loops so that the computational workload is larger for each thread.

