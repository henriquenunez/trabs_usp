CC=gcc
CFLAGS=-Wall

CURR_DIR=$(pwd)
blddir=.#${CURR_DIR}/build

all: clean dirs build

dirs:
	#mkdir ${blddir}
	#mkdir ${blddir}/release

build: nodes.o stack.o queue.o lot.o main.o

nodes.o:
	${CC} ${CFLAGS} -g -c nodes.c -o ${blddir}/nodes.o


stack.o:
	${CC} ${CFLAGS} -g -c stack.c -o ${blddir}/stack.o


queue.o:
	${CC} ${CFLAGS} -g -c queue.c -o ${blddir}/queue.o

lot.o:
	${CC} ${CFLAGS} -g -c lot.c -o ${blddir}/lot.o

main.o:
	${CC} ${CFLAGS} -g main.c ${blddir}/*.o -o ${blddir}/parkingLot

run:
	${blddir}/parkingLot

clean:
	rm -rf *.o parkingLot
