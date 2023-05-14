CFLAGS = -std=gnu11 -Wall -Wextra -lm -O1 -fopenmp -fopt-info-vec
DEBUG = -g
TARGETS = reference omp_vectorized reference_double omp_vectorized_double
LIBS = ../../tools/csv/csv.c ../../tools/time/time.c
CC = gcc

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	$(RM) $(TARGETS) 

reference: omp_vec.c $(LIBS)
	$(CC) $(CFLAGS) -DNAME='"reference"' -o $@ $^

omp_vectorized: omp_vec.c $(LIBS)
	$(CC) $(CFLAGS) -DVECTORIZE -DNAME='"vectorized"' -o $@ $^

reference_double: omp_vec_double.c $(LIBS)
	$(CC) $(CFLAGS) -DNAME='"reference_double"' -o $@ $^

omp_vectorized_double: omp_vec_double.c $(LIBS)
	$(CC) $(CFLAGS) -DVECTORIZE -DNAME='"vectorized_double"' -o $@ $^

%: %.c $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

