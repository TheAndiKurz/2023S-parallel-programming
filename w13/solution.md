The first thing I did, was using loop tiling proposed in the lecture, while parallizing the outer 3 loops. The loop tiling should improve cache performance, while the parallization reduces compute time. 
Then I swiched the inner 2 loops to again improve cache performance. 
These changes already reduce the execution time on the lcc2 (compiling both with -O3) from 600 seconds to 1.43 seconds. 

Then I introduced simd vectorization using openMP. For that I had to transpose the matrix B first and switched the inner loops back. Then I used the omp simd pragma with a reduction using `+`, using a local variable first, and then storing it to the matrix. 
This reduces the execution time to 1.2 seconds.