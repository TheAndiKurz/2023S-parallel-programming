.PHONY = all clean
CC = gcc

CFLAGS = -std=c11 -Wall -Werror -Wextra -Wpedantic -fopenmp
LFLAGS =

LIBS = ../../tools/csv/csv.c ../../tools/time/time.c

BINS = task2

OPTIMIZATIONS =  -O1

all: $(BINS)

task2: task2.o $(LIBS)
	# Compile the target with different optimization levels
	for opt in $(OPTIMIZATIONS); do \
		$(CC) $(CFLAGS) $$opt $^ -o $@_$$opt; \
	done

task2.o: task2.c
	$(CC) $(CFLAGS) $(LFLAGS) -c $<

clean:
	@rm -f *.o $(BINS) flush_-*
