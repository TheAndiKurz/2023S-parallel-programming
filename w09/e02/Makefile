CC=gcc
CC_FLAGS= -O2 -ftree-vectorize -fopt-info-vec-all-internals


.PHONEY: all
all: real

SRC=$(wildcard *.c) 

analysis: $(SRC)
	@$(CC) $(SRC) -o analysis $(CC_FLAGS)

analysis.txt: $(SRC)
	@$(CC) $(SRC) -o analysis $(CC_FLAGS) | tee analysis.txt

.PHONEY: clean
clean:
	@rm analysis

