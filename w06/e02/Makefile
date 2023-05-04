# Variables
CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = $(wildcard *.c)
EXEC = $(SRC:%.c=%)

# Rules
all: $(EXEC)

%: %.c
	$(CC) $(CFLAGS) -c $< -o $@_seq
	$(CC) $(CFLAGS) -c $< -o $@_par -DPARALLEL


clean:
	rm -f *_seq *_par

.PHONY: all