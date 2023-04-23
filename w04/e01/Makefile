CFLAGS = -std=gnu11 -Wall -Wextra -lm -O3 -fopenmp -g
CC = gcc-10
LIBS = ../../tools/csv/csv.c ../../tools/time/time.c

TARGETS = atomic_increase

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	$(RM) $(TARGETS)

install:
	sudo apt install gcc-10

atomic_increase: atomic_increase.c $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

