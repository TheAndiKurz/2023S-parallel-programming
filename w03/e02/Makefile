
.PHONY =  all clean
CC = gcc

CFLAGS = -std=c11 -Wall -Werror -Wextra -Wpedantic -fopenmp
LFLAGS =

BINS = ex2

all: ${BINS}

ex2: ex2.o
	$(CC) $^ $(CFLAGS) -o $@

ex2.o: ex2.c
	$(CC) $(LFLAGS) -c $<

run: all
	./ex2 && make clean
clean:
	@rm *.o ${BINS}

