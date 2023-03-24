#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name s01e02_fa
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive


# run file $1 with $2 num threads
runNTimes () {
  for n in $(seq $2); do
    echo -n $1,  
    ./mandelbrot$1
    echo ""
  done
}

# echo header
echo "optimization, time"

# 
for o in O0 O1 O2 O3 Ofast Os; do
  runNTimes o 10
done
