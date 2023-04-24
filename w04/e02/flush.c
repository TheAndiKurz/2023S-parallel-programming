#include <omp.h>
#include <stdio.h>

int main() {
    int data, flag = 0;
#pragma omp parallel num_threads(2)
    {
        if(omp_get_thread_num() == 0) {
            /* Write to the data buffer that will be read by thread */
            data = 42;
            // #pragma omp flush(data) // data was changed
            /* Set flag to release thread 1 */
            flag = 1; // flag was changed
            // #pragma omp flush(flag)
        } else if(omp_get_thread_num() == 1) {
            /* Loop until we see the update to the flag */
            // #pragma omp flush(flag) // check flag
            while(flag < 1) {
            // #pragma omp flush(flag) // check flag
            }
            printf("flag=%d data=%d\n", flag, data);
        }
    }
    return 0;
}
