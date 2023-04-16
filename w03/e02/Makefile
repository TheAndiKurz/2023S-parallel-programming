.PHONY = all clean
CC = gcc

CFLAGS = -std=c11 -Wall -Werror -Wextra -Wpedantic -fopenmp
LFLAGS =

LIBS = ../../tools/csv/csv.c ../../tools/time/time.c

BINS = ex2 ex2_optimized

OPTIMIZATIONS =  -O0 -O1 -O2 -O3 -Ofast -Os

all: $(BINS)

ex2: ex2.o $(LIBS)
	# Compile the target with different optimization levels
	for opt in $(OPTIMIZATIONS); do \
		$(CC) $(CFLAGS) $$opt $^ -o $@_$$opt; \
	done

ex2.o: ex2.c
	$(CC) $(CFLAGS) $(LFLAGS) -c $<

ex2_optimized: ex2_optimized.o $(LIBS)
	# Compile the target with different optimization levels
	for opt in $(OPTIMIZATIONS); do \
		$(CC) $(CFLAGS) $$opt $^ -o $@_$$opt; \
	done

ex2_optimized.o: ex2_optimized.c
	$(CC) $(CFLAGS) $(LFLAGS) -c $<

clean:
	@rm -f *.o $(BINS) ex2_* ex2_optimized_*
