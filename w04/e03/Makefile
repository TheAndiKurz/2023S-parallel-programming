CFLAGS = -std=gnu11 -Wall -Wextra -lm -O3 -g -fopenmp
DEBUG = -fsanitize=address
TARGETS = mergesort_seq mergesort_par mergesort_halfpar
LIBS = ../../tools/csv/csv.c ../../tools/time/time.c
CC = /usr/local/bin/gcc-12

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	$(RM) $(TARGETS)

mergesort_seq: mergesort_seq.c $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

mergesort_par: mergesort_par.c $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^
	
mergesort_halfpar: mergesort_halfpar.c $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^
