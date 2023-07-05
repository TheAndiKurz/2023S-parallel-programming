CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp -O3
DEBUG = -g
TARGETS = mm
LIBS = ../../tools/csv/csv.c ../../tools/time/time.c
CC = /usr/local/bin/gcc-13 

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	@$(RM) $(TARGETS) 

mm: mm.c
	$(CC) $(CFLAGS) -o $@ $^
