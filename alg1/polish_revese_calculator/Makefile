CC=gcc
CFLAGS=-Wall
COMMENTS=


CURR_DIR=$(pwd)
blddir=.#${CURR_DIR}/build
TARGET=polish_calc

src = $(wildcard *.c)
obj = $(src:.c=.o)

all: clean build
	gcc -g -o ${TARGET} main.c *.o ${CFLAGS} 
build: nodes.o tree.o stack.o calculator.o

tests: build
	gcc -g -o test_tree test_tree.c *.o ${CFLAGS}
	gcc -g -o test_calculator test_calculator.c *.o ${CFLAGS}

calculator.o:
	gcc -g -c -o $@ calculator.c ${CFLAGS}

tree.o:
	gcc -g -c -o $@ bin_tree.c ${CFLAGS}

stack.o:
	gcc -g -c -o $@ stack.c ${CFLAGS}

nodes.o:
	gcc -g -c -o $@ nodes.c ${CFLAGS}

run:
	./${TARGET}

.PHONY: clean

clean:
	rm -rf $(obj) ${TARGET} pilhachu kiwi test_tree test_calculator *.o
