CC = gcc
CFLAGS = -fopenmp -std=gnu11 -O3
TARGETS = slow fast

all: $(TARGETS)

slow: slow.c
	$(CC) $(CFLAGS) -o $@ $<

fast: fast.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -f $(TARGETS)

