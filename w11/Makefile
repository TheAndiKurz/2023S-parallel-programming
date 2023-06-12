# Variables
CC = gcc
CFLAGS = -std=gnu11 -Wall -Wextra -lm -O3 -fopenmp -g -Wno-strict-aliasing
LIBS = $(wildcard ../tools/**/*.c)
SRC = $(wildcard *.c)
EXEC = nBody

# Rules
all: $(EXEC)

%: %.c $(LIBS) $(SRC)
	$(CC) $^ -o $@_seq $(CFLAGS)
	$(CC) $^ -o $@_par -DPARALLEL $(CFLAGS)

clean:
	rm -f *_seq *_par

plot:
	gnuplot particle.plt

.PHONY: all