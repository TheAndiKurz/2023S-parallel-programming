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


for i in {1..6}; do
  # Run with different number tasks for 1 to 8 threads
  for t in {1..15}; do
    # parallel recursive for optimal number of tasks
    for n in 1 2 4 8; do
        OMP_NUM_THREADS=${n} ./delannoy_number_par_recursive 12 -t $((3**${t})) -w t
    done
  done
done

mv times.csv times_number_tasks.csv

