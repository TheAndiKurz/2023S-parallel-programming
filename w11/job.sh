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

for i in {1..2}; do
    for particles in 100 500 1000 2500 5000; do
        echo "particles: $particles"
        ./nBody_seq $particles 100

        for threads in 1 2 4 8; do
            export OMP_NUM_THREADS=$threads
            echo "threads: $threads"
            ./nBody_par $particles 100
        done
    done
done
