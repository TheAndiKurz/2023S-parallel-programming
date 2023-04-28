CFLAGS = -std=gnu11 -Wall -Wextra -lm -O3 -fopenmp
DEBUG = -fsanitize=address
TARGETS = delannoy_number_seq_array delannoy_number_seq_malloc delannoy_number_seq_rows delannoy_number_seq_srows delannoy_number_seq_recursive delannoy_number_par_recursive delannoy_number_par_nrecursive
LIBS = ../../tools/csv/csv.c ../../tools/time/time.c
CC = /usr/local/bin/gcc-12

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	$(RM) $(TARGETS) 

%: %.c $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

delannoy_number_seq_array: delannoy_number_seq.c $(LIBS)
	$(CC) $(CFLAGS) -DVERSION=1 -o $@ $^

delannoy_number_seq_malloc: delannoy_number_seq.c $(LIBS)
	$(CC) $(CFLAGS) -DVERSION=2 -o $@ $^

delannoy_number_seq_rows: delannoy_number_seq.c $(LIBS)
	$(CC) $(CFLAGS) -DVERSION=3 -o $@ $^

delannoy_number_seq_srows: delannoy_number_seq.c $(LIBS)
	$(CC) $(CFLAGS) -DVERSION=4 -o $@ $^

delannoy_number_seq_recursive: delannoy_number_seq.c $(LIBS)
	$(CC) $(CFLAGS) -DVERSION=5 -o $@ $^
