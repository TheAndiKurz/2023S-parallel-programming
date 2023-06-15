CFLAGS = -std=gnu11 -Wall -Wextra -lm -O3
DEBUG = -g
TARGETS = A A_SOL B B_SOL C C_SOL D D_SOL E E_SOL F F_SOL G G_SOL
CC = /usr/local/bin/gcc-13

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	$(RM) $(TARGETS) 

%: loop_optimizations.c
	$(CC) $(CFLAGS) -D$@ -o $@ $^
