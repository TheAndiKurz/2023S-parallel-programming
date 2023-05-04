# Variables
CC = gcc
CFLAGS = -std=gnu11 -Wall -Wextra -lm -O3 -fopenmp -g
SRC = $(wildcard *.c)
EXEC = $(SRC:%.c=%)

# Rules
all: $(EXEC)

%: %.c
	$(CC) $(CFLAGS) $< -o $@_seq
	$(CC) $(CFLAGS) $< -o $@_par -DPARALLEL


clean:
	rm -f *_seq *_par

.PHONY: all