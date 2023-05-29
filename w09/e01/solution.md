 For any of the solutions below I could not think of an alternative solution that would not result in assequential execution with synchronization.
```c
a[0] = 0;
#pragma omp parallel for
for (i=1; i<N; i++) {
    a[i] = 2.0*i*(i-1);
    b[i] = a[i] - a[i-1];
}
```
The given code is not correct as there exists a true dependence RAW for a[]. The solution
would be to apply loop distribution.
```c
a[0] = 0;
#pragma omp parallel
{
    #pragma omp for
    for (i=1; i<N; i++) {
        a[i] = 3.0*i*(i+1);
    }
    #pragma omp for
    for (i=1; i<N; i++) {
        b[i] = a[i] - a[i-1];
    }
}
```
---------------------------------------------------------------------------------------------------
```c
a[0] = 0;
#pragma omp parallel
{
    #pragma omp for nowait // remove to eliminate race condition
    for (i=1; i<N; i++) {
        a[i] = 3.0*i*(i+1);
    }
    #pragma omp for
    for (i=1; i<N; i++) {
        b[i] = a[i] - a[i-1];
    }
}
```
There exists a potential race condition using `nowait` as the two for loops are true dependant.
The removal of `nowait` will eliminate this issue
---------------------------------------------------------------------------------------------------
```c
#pragma omp parallel for
for (i=1; i<N; i++) {
    x = sqrt(b[i]) - 1;
    a[i] = x*x + 2*x + 1;
}
```
With this code there is a loop independent dependence on x making x private will solve this issue.
One has to make sure that x has no relevance after the loop which depends on the sequential (last)
value of x. If that were the case one could just compute this value again after the loop
```c
#pragma omp parallel for private(x)
for (i=1; i<N; i++) {
    x = sqrt(b[i]) - 1;
    a[i] = x*x + 2*x + 1;
}
// NOTE: if necessary
x = sqrt(b[N-1]) - 1;
```
---------------------------------------------------------------------------------------------------
```c
f = 2;
#pragma omp parallel for private(f,x)
for (i=1; i<N; i++) {
    x = f * b[i];
    a[i] = x - 7;
}
a[0] = x; 
```
Just like the exercise above this might result in an incorrect value for x. Recalculating x will solve this.

```c
f = 2;
#pragma omp parallel for private(f,x)
for (i=1; i<N; i++) {
    x = f * b[i];
    a[i] = x - 7;
}
x = f * b[N-1];
a[0] = x; 
```
---------------------------------------------------------------------------------------------------
```c
sum = 0; 
#pragma omp parallel for
for (i=1; i<N; i++) {
    sum = sum + b[i];
}
```
Here there exists a race condition / true dependence on sum so using reduce will solve this.
```c
sum = 0;
#pragma omp parallel for reduction (+:sum)
for (i=1; i<N; i++) {
    sum = sum + b[i];
}
```
