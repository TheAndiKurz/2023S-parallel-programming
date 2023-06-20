
for i in {1..100}; do 
  for t in 1 2 4; do 
    OMP_NUM_THREADS=${t} ./prefix_sum_par_test 5000000
    OMP_NUM_THREADS=${t} ./prefix_sum_par_test2 5000000
  done
done

mv times.csv times_big_n2.csv
