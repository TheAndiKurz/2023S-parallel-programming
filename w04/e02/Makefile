.PHONY = all clean
CC = gcc

CFLAGS = -std=c11 -Wall -Werror -Wextra -Wpedantic -fopenmp
LFLAGS =

LIBS = ../../tools/csv/csv.c ../../tools/time/time.c

BINS = flush

OPTIMIZATIONS =  -O3

all: $(BINS)

flush: flush.o
	# Compile the target with different optimization levels
	for opt in $(OPTIMIZATIONS); do \
		$(CC) $(CFLAGS) $$opt $^ -o $@_$$opt; \
	done

flush.o: flush.c
	$(CC) $(CFLAGS) $(LFLAGS) -c $<

clean:
	@rm -f *.o $(BINS) flush_-*
