CC=gcc
CC_FLAGS=-O3 -g3 -lm

.PHONEY: all
all: real

SRC=$(wildcard *.c)

real: $(SRC)
	@$(CC) $(SRC) -o real $(CC_FLAGS)

.PHONEY: clean
clean:
	@rm real

.PHONEY: run
run: all
	@echo "Sequential:"
	@./real
	@echo
