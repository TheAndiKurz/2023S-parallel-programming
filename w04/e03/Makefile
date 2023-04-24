CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp -O3 -g 
TARGETS = mergesort_seq mergesort_par
LIBS = ../../tools/csv/csv.c ../../tools/time/time.c

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	$(RM) $(TARGETS)

mergesort_seq: mergesort_seq.c $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

mergesort_par: mergesort_par.c $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^
