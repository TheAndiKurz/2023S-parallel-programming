# Variables
CC = gcc
CFLAGS = -std=gnu11 -Wall -Wextra -lm -O1 -g -fopenmp
LIBS = $(wildcard ../../tools/**/*.c)
SRC = $(wildcard *.c)
EXEC = $(SRC:%.c=%)

# Rules
all: $(EXEC)

%: %.c $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@_vec -DVECTORIZE
	$(CC) $(CFLAGS) $^ -o $@_not_vec

plot:
	python3 ../../tools/plot.py -l -x "Vector Size" -t "Execution Time by Vector Size"

clean:
	rm -f $(EXEC)_*

.PHONY: all