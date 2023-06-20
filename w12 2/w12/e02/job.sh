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

echo "A"
echo "  Reference:" \n
perf stat ./A 
echo "  Transformed:" \n
perf stat ./A_SOL
echo "B"
echo "  Reference:" \n
perf stat ./B
echo "  Transformed:" \n
perf stat ./B_SOL
echo "C"
echo "  Reference:" \n
perf stat ./C
echo "  Transformed:" \n
perf stat ./C_SOL
echo "D"
echo "  Reference:" \n
perf stat ./D
echo "  Transformed:" \n
perf stat ./D_SOL
echo "E"
echo "  Reference:" \n
perf stat ./E
echo "  Transformed:" \n
perf stat ./E_SOL
echo "F"
echo "  Reference:" \n
perf stat ./F
echo "  Transformed:" \n
perf stat ./F_SOL
echo "G"
echo "  Reference:" \n
perf stat ./G
echo "  Transformed:" \n
perf stat ./G_SOL

