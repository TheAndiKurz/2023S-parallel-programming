CFLAGS = -std=gnu11 -Wall -Wextra -lm -O3 -fopenmp
DEBUG = -g
TARGETS = prefix_sum_seq prefix_sum_par prefix_sum_par_test
LIBS = ../../tools/csv/csv.c ../../tools/time/time.c
CC = /usr/local/bin/gcc-13

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	$(RM) $(TARGETS) 

%: %.c $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

