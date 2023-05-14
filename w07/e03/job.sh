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

for i in {1..5}; do
  for n in {4..13}; do
    m=$((2**${n}))
    echo "Vector size: ${m}"
    ./manuel_vectorization_vec ${m}
    ./manuel_vectorization_no_vec ${m} 
  done
done
