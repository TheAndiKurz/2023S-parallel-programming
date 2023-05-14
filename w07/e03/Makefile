# Variables
CC = gcc
CFLAGS = -std=gnu11 -Wall -Wextra -lm -O1 -g -fopenmp
LIBS = $(wildcard ../../tools/**/*.c)
SRC = $(wildcard *.c)
EXEC = $(SRC:%.c=%)

# Rules
all: $(EXEC)

%: %.c $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@_vec -DVECTORICE
	$(CC) $(CFLAGS) $^ -o $@_not_vec


clean:
	rm -f $(EXEC)_*

.PHONY: all