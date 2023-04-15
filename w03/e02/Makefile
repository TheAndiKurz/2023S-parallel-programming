
.PHONY =  all clean
CC = gcc

CFLAGS = -std=c11 -Wall -Werror -Wextra -Wpedantic -fopenmp
LFLAGS =

BINS = ex2 ex2_blocks ex2_padding ex2_optimized

all: ${BINS}

ex2: ex2.o
	$(CC) $^ $(CFLAGS) -o $@

ex2.o: ex2.c
	$(CC) $(LFLAGS) -c $<

ex2_blocks: ex2.o
	$(CC) $^ $(CFLAGS) -DBLOCKS -o $@

ex2_padding: ex2.o
	$(CC) $^ $(CFLAGS) -DPADDING -o $@

ex2_optimized: ex2.o
	$(CC) $^ $(CFLAGS) -DOPTIMIZED -o $@

clean:
	@rm *.o ${BINS}

