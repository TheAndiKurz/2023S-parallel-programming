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

files=(A B C D E F G)

for f in files; do
    echo "File: ${f}"
    echo "  Reference:" \n
    perf stat -e cycles,instructions,cache-references,cache-misses,branches,branch-misses ./${f} 
    echo "  Transformed:" \n
    perf stat -e cycles,instructions,cache-references,cache-misses,branches,branch-misses ./${f}_OPT
done

