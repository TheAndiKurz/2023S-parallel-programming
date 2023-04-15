.PHONY = all clean
CC = gcc

CFLAGS = -std=c11 -Wall -Werror -Wextra -Wpedantic -fopenmp
LFLAGS =

LIBS = ../../tools/csv/csv.c ../../tools/time/time.c

BINS = ex2 ex2_blocks ex2_padding ex2_optimized

all: $(BINS)

ex2: ex2.o $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@

ex2.o: ex2.c
	$(CC) $(CFLAGS) $(LFLAGS) -c $<

ex2_blocks: ex2.o $(LIBS)
	$(CC) $(CFLAGS) -DBLOCKS $^ -o $@

ex2_padding: ex2.o $(LIBS)
	$(CC) $(CFLAGS) -DPADDING $^ -o $@

ex2_optimized: ex2.o $(LIBS)
	$(CC) $(CFLAGS) -DOPTIMIZED $^ -o $@

clean:
	@rm -f *.o $(BINS)
