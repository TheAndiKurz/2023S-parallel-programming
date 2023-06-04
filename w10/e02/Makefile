CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp
DEBUG = -g
TARGETS = a a_parallel b b_parallel c c_parallel
LIBS = ../../tools/csv/csv.c ../../tools/time/time.c
CC = gcc

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	@$(RM) $(TARGETS) 

a: a.c $(LIBS)
	@$(CC) $(CFLAGS)  -o $@ $^

a_parallel: a_parallel.c $(LIBS)
	@$(CC) $(CFLAGS)  -o $@ $^

b: b.c $(LIBS)
	@$(CC) $(CFLAGS)  -o $@ $^

b_parallel: b_parallel.c $(LIBS)
	@$(CC) $(CFLAGS)  -o $@ $^

c: c.c $(LIBS)
	@$(CC) $(CFLAGS)  -o $@ $^

c_parallel: c_parallel.c $(LIBS)
	@$(CC) $(CFLAGS)  -o $@ $^

%: %.c $(LIBS)
	@$(CC) $(CFLAGS) -o $@ $^

