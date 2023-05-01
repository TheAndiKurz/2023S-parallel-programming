CFLAGS = -std=gnu11 -Wall -Wextra -lm -O3 -fopenmp -g
LIBS = ../../tools/csv/csv.c ../../tools/time/time.c
TARGETS = heat_stencil_2D_seq heat_stencil_2D_omp

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	$(RM) $(TARGETS)

heat_stencil_2D_seq: heat_stencil_2D.c $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@

heat_stencil_2D_omp: heat_stencil_2D.c $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@ -DPARALLEL

