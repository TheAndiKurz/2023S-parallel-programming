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


for n in 100 500 1000 5000 10000 50000 100000; do
    echo "-----------------"
    echo "n: $n"
    echo "-----------------"


    for _ in {1..2}; do
        ./heat_stencil_2D_seq $n

        for threads in 2 4 8; do
            export OMP_NUM_THREADS=$threads
            echo "-----------------"
            echo "threads: $threads"
            echo "-----------------"
            
            ./heat_stencil_2D_omp $n
        done

    done
    
done
