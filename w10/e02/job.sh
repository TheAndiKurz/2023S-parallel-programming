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


# for threads in [1, 2, 4, 8] use monte_carlo with 500000000 samples
for threads in 1 2 4 8; do
  export OMP_NUM_THREADS=$threads
  echo "threads: $threads"
   for i in {1..5}; do
    ./a 200000000
    ./a_parallel 200000000
  done
done

