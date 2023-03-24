CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp
CC     = /usr/local/bin/gcc

OPTIMIZED_FILES=$(addprefix mandelbrot, O0 O1 O2 O3 Ofast Os O3_ffast-math)

.PHONY: all
all: mandelbrot ${OPTIMIZED_FILES}

.PHONY: clean
clean:
	$(RM) mandelbrot mandelbrot.png ${OPTIMIZED_FILES}

mandelbrot: mandelbrot.c

%O0: %.c
	${CC} $< -o $@ ${CFLAGS} -O0

%O1: %.c
	${CC} $< -o $@ ${CFLAGS} -O1

%O2: %.c
	${CC} $< -o $@ ${CFLAGS} -O2

%O3: %.c
	${CC} $< -o $@ ${CFLAGS} -O3

%Ofast: %.c
	${CC} $< -o $@ ${CFLAGS} -Ofast

%Os: %.c
	${CC} $< -o $@ ${CFLAGS} -Os

%O3_ffast-math: %.c
		${CC} $< -o $@ ${CFLAGS} -O3 -ffast-math
