#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name test
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

for size in 500 1000 10000 100000 10000000 100000000; do 
  echo "sequential | size: $size"
  for n in {1..4}; do 
    ./mergesort_seq $size
  done
  for threads in 1 2 4; do
    export OMP_NUM_THREADS=$threads
    echo "threads: $threads | size: $size"
    for n in {1..4}; do 
      ./mergesort_par $size
    done
  done
done
