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
  # Run fast versions for larger n (limted by max stack size for array)
  for n in 25 50 75 100 250 500 750 1000; do 
    for t in array malloc rows srows; do 
      ./delannoy_number_seq_$t $n
    done
  done

  # Run fast versions for even larger n
  for n in 2500 5000 7500 10000 25000 50000; do 
    for t in malloc rows srows; do 
      ./delannoy_number_seq_$t $n
    done
  done

  # Bring fastest versions to limit
  for n in 75000 100000 250000; do 
    for t in rows srows; do 
      ./delannoy_number_seq_$t $n
    done
  done
done

mv ./times.csv ./times_big_n.csv 
