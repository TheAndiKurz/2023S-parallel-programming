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

for i in {1..10}; do
  for n in 1024 2048 4096; do
    echo "Vector size: ${n}"
    ./reference ${n}
    ./omp_vectorized ${n} 
    ./reference_double ${n}
    ./omp_vectorized_double ${n} 
  done
done

mv ./times.csv ./times_n_local.csv 

