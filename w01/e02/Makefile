CC = gcc
CFLAGS = -fopenmp -std=gnu11
TARGETS = slow medium fast

all: $(TARGETS)

slow: slow.c
	$(CC) $(CFLAGS) -o $@ $<

medium: medium.c
	$(CC) $(CFLAGS) -o $@ $<

fast: fast.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -f $(TARGETS)

