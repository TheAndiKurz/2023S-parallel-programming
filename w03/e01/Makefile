CFLAGS = -std=gnu11 -Wall -Wextra -lm -O3 -fopenmp -g
TARGETS = monte_carlo_atomic monte_carlo_critical monte_carlo_reduction 
LIBS = ../../tools/csv/csv.c ../../tools/time/time.c

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	$(RM) $(TARGETS)

monte_carlo_critical: monte_carlo.c $(LIBS)
	$(CC) $(CFLAGS) -DCRITICAL -o $@ $^

monte_carlo_atomic: monte_carlo.c $(LIBS)
	$(CC) $(CFLAGS) -DATOMIC -o $@ $^

monte_carlo_reduction: monte_carlo.c $(LIBS)
	$(CC) $(CFLAGS) -DREDUCTION -o $@ $^