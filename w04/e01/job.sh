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


n=250000000

export OMP_NUM_THREADS=4

for place in "cores(1)" "threads(4)" "sockets(1)"; do
    export OMP_PLACES=$place
    echo "-----------------"
    echo "place: $place"
    echo "-----------------"
    
    for _ in {1..5}; do
        echo "-----------------"
        echo "affinity: none"
        echo "-----------------"
        ./atomic_increase $n
        for affinity in master close spread; do
            echo "-----------------"
            echo "affinity: $affinity"
            echo "-----------------"
            OMP_PROC_BIND=$affinity ./atomic_increase $n
        done
    done
done