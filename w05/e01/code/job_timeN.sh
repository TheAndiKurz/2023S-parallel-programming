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
  # Run all versions for small n
  for n in 6 7 8 9 10 11; do
    # sequential versions
    for t in recursive; do 
      ./delannoy_number_seq_$t $n
    done
    # parallel recursive for optimal number of tasks
    OMP_NUM_THREADS=1 ./delannoy_number_par_recursive ${n} -t 4
    OMP_NUM_THREADS=2 ./delannoy_number_par_recursive ${n} -t 4
    OMP_NUM_THREADS=4 ./delannoy_number_par_recursive ${n} -t 10
    OMP_NUM_THREADS=8 ./delannoy_number_par_recursive ${n} -t 10
    # naive parallel recursive, spawning tasks every function call
    OMP_NUM_THREADS=1 ./delannoy_number_par_nrecursive ${n}
    OMP_NUM_THREADS=2 ./delannoy_number_par_nrecursive ${n}
    OMP_NUM_THREADS=4 ./delannoy_number_par_nrecursive ${n}
    OMP_NUM_THREADS=8 ./delannoy_number_par_nrecursive ${n}
  done

  for n in 12 13 14 15; do
    # sequential versions
    for t in recursive; do 
      ./delannoy_number_seq_$t $n
    done
    # parallel recursive for optimal number of tasks
    OMP_NUM_THREADS=1 ./delannoy_number_par_recursive ${n} -t 4
    OMP_NUM_THREADS=2 ./delannoy_number_par_recursive ${n} -t 4
    OMP_NUM_THREADS=4 ./delannoy_number_par_recursive ${n} -t 10
    OMP_NUM_THREADS=8 ./delannoy_number_par_recursive ${n} -t 10
  done
done
mv ./times.csv ./times_n.csv 
