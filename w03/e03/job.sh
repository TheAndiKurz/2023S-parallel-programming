#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name test
# Redirect output stream to this file
#SBATCH --output=output_comp.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

# number of samples taken
n=100000000

# for threads in [1, 2, 4, 8] use monte_carlo with n samples
for threads in 1 2 4 8; do
  export OMP_NUM_THREADS=$threads
  echo "threads: $threads"
  ./monte_carlo_local_sum $threads $n
  ./monte_carlo_array $threads $n
  ./monte_carlo_array_56 $threads $n
done
