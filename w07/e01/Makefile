CFLAGS = -std=gnu11 -Wall -Wextra -lm -O1 -fopenmp -fopt-info-vec
DEBUG = -g
TARGETS = reference vectorized
LIBS = ../../tools/csv/csv.c ../../tools/time/time.c
CC = /usr/local/bin/gcc-13

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	$(RM) $(TARGETS) 

reference: auto_vec.c $(LIBS)
	$(CC) $(CFLAGS) -DNAME='"reference"' -o $@ $^

vectorized: auto_vec.c $(LIBS)
	$(CC) $(CFLAGS) -ftree-vectorize -DNAME='"vectorized"' -o $@ $^

%: %.c $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

