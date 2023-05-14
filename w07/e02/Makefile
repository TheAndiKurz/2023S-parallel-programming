CFLAGS = -std=gnu11 -Wall -Wextra -lm -O1 -fopenmp -fopt-info-vec
DEBUG = -g
TARGETS = reference omp_vectorized
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

%: %.c $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

