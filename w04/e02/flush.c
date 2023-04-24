#include <omp.h>
#include <stdio.h>

int main() {
    int data, flag = 0;
#pragma omp parallel num_threads(2)
    {
        if(omp_get_thread_num() == 0) {
            /* Write to the data buffer that will be read by thread */
            data = 42;
#pragma omp flush(data)
            /* Set flag to release thread 1 */
            flag = 1;
#pragma omp flush(flag)
            /* #pragma omp flush(flag, data) this would seem to work aswell but the order of these
               flushes is not guaranteed and therefore there could be a race condition again.
               a very similar example was shown in the lecture */

        } else if(omp_get_thread_num() == 1) {
            /* Loop until we see the update to the flag */
#pragma omp flush(flag)
            while(flag < 1) {
#pragma omp flush(flag)
            }
            /* print flag and data */
#pragma omp flush(data)
            printf("flag=%d data=%d\n", flag, data);
        }
    }
    return 0;
}
