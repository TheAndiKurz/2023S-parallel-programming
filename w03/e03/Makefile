CFLAGS = -std=gnu11 -Wall -Wextra -lm -O3 -fopenmp -g
TARGETS = monte_carlo_local_sum monte_carlo_array monte_carlo_array_8 
LIBS = ../../tools/csv/csv.c ../../tools/time/time.c

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	$(RM) $(TARGETS)

monte_carlo_local_sum: monte_carlo_local_sum.c $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

monte_carlo_array: monte_carlo_array.c $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

monte_carlo_array_8: monte_carlo_array.c $(LIBS)
	$(CC) $(CFLAGS) -DPADDING=8 -o $@ $^
