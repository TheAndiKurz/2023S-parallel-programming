CC=gcc
CC_FLAGS= -O3 -g3 -lm -pg

.PHONEY: all
all: real

SRC=$(wildcard *.c)

real: $(SRC)
	@$(CC) $(SRC) -o real $(CC_FLAGS)

.PHONEY: clean
clean:
	@rm real analysis.txt

analysis.txt: real
	@ ./real
	@ gprof ./real gmon.out >> $@

.PHONEY: run
run: all
	@echo "Sequential:"
	@./real
	@echo
