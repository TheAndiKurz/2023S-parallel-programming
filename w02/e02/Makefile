
.PHONY =  all clean
CC = gcc

CFLAGS = -std=c11 -Wall -Werror -Wextra -Wpedantic
LFLAGS =

BINS = row_major_hadamard column_major_hadamard

all: ${BINS}

row_major_hadamard: row_major_hadamard.o
	$(CC) $^ $(CFLAGS) -o $@

row_major_hadamard.o: row_major_hadamard.c
	$(CC) $(LFLAGS) -c $<

column_major_hadamard: column_major_hadamard.o
	$(CC) $^ $(CFLAGS) -o $@

column_major_hadamard.o: column_major_hadamard.c
	$(CC) $(LFLAGS) -c $<

run: all
	./row_major_hadamard && ./column_major_hadamard make clean
clean:
	@rm *.o ${BINS}

