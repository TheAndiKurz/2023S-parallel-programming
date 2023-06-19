CFLAGS = -std=gnu11 -Wall -Wextra -lm -O3 -fopenmp
DEBUG = -g 
TARGETS = A A_SOL B B_SOL C C_SOL D D_SOL E E_SOL F F_SOL G G_SOL 
CC = /usr/local/bin/gcc-13 

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	$(RM) $(TARGETS) 


A: loop_optimizations.c
	$(CC) $(CFLAGS) -DTIME -DVERSION=A -o A $^

A_SOL: loop_optimizations.c
	$(CC) $(CFLAGS) -DTIME -DVERSION=A_SOL -o A_SOL $^

B: loop_optimizations.c
	$(CC) $(CFLAGS) -DTIME -DVERSION=B -o B $^

B_SOL: loop_optimizations.c
	$(CC) $(CFLAGS) -DTIME -DVERSION=B_SOL -o B_SOL $^

C: loop_optimizations.c
	$(CC) $(CFLAGS) -DTIME -DVERSION=C -o C $^

C_SOL: loop_optimizations.c
	$(CC) $(CFLAGS) -DTIME -DVERSION=C_SOL -o C_SOL $^

D: loop_optimizations.c
	$(CC) $(CFLAGS) -DTIME -DVERSION=D -o D $^

D_SOL: loop_optimizations.c
	$(CC) $(CFLAGS) -DTIME -DVERSION=D_SOL -o D_SOL $^

E: loop_optimizations.c
	$(CC) $(CFLAGS) -DTIME -DVERSION=E -o E $^

E_SOL: loop_optimizations.c
	$(CC) $(CFLAGS) -DTIME -DVERSION=E_SOL -o E_SOL $^

F: loop_optimizations.c
	$(CC) $(CFLAGS) -DTIME -DVERSION=F -o F $^

F_SOL: loop_optimizations.c
	$(CC) $(CFLAGS) -DTIME -DVERSION=F_SOL -o F_SOL $^

G: loop_optimizations.c
	$(CC) $(CFLAGS) -DTIME -DVERSION=G -o G $^

G_SOL: loop_optimizations.c
	$(CC) $(CFLAGS) -DTIME -DVERSION=G_SOL -o G_SOL $^


