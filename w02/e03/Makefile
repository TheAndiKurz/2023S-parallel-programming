CFLAGS = -std=gnu11 -Wall -Wextra -lm -O3 -pthread -fopenmp
TARGETS = serial_monte_carlo parallel_monte_carlo omp_parallel_monte_carlo 


.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	$(RM) $(TARGETS)

serial_monte_carlo: serial_monte_carlo.c

parallel_monte_carlo: parallel_monte_carlo.c

omp_parallel_monte_carlo: omp_parallel_monte_carlo.c