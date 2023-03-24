#include <stdio.h>
#include <omp.h>


double start_to_record(){
  return omp_get_wtime();
}

void stop_record(double start){
  double end = start_to_record();
  printf("%2.4f", end - start);
}
