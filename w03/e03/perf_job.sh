#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name test
# Redirect output stream to this file
#SBATCH --output=output_perf.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

n=10000000
threads=8

# use monte_carlo with n samples and threads threads
export OMP_NUM_THREADS=$threads
echo "threads: $threads"
perf stat -d -d ./monte_carlo_local_sum $threads $n
perf stat -d -d ./monte_carlo_array $threads $n
perf stat -d -d ./monte_carlo_array_8 $threads $n
perf stat -d -d ./monte_carlo_array_56 $threads $n
