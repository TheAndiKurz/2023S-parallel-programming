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

for i in {1..4}; do
  # Run all versions for small n
  for n in {4..30}; do
    m=$((2**${n}))
    # sequential version 
    ./prefix_sum_seq ${m}
    # parallel version for threads in 1 2 4 8
    for t in 1 2 4; do
      OMP_NUM_THREADS=${t} ./prefix_sum_par ${m}
      OMP_NUM_THREADS=${t} ./prefix_sum_par_test ${m}
    done
  done
done

mv ./times.csv ./times_n.csv 

