CC=gcc
CC_FLAGS= -O3 -g3 -lm -fopenmp


.PHONEY: all
all: real

SRC=$(wildcard *.c) ../../tools/csv/csv.c ../../tools/time/time.c

real: $(SRC)
	@$(CC) $(SRC) -o real $(CC_FLAGS) -pg

real_test: $(SRC)
	@$(CC) $(SRC) -o real $(CC_FLAGS) -ftree-vectorize -march=native

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
