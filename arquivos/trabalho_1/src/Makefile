CFLAGS = -g
LDFLAGS = -fsanitize=address
BIN_DIR = ./bin

all: build

build: build_dir
	gcc ${CFLAGS} main.c -o ${BIN_DIR}/trab ${LDFLAGS}

csv.o: build_dir
	gcc -g -c csv.c -o ${BIN_DIR}/csv.o ${LDFLAGS}

tests: clean csv.o
	gcc -g testcsvreader.c ${BIN_DIR}/csv.o -o ${BIN_DIR}/testcsvreader ${LDFLAGS}
	${BIN_DIR}/testcsvreader

run:
	${BIN_DIR}/trab

zip: clean
	zip ../src.zip *

build_dir:
	mkdir ${BIN_DIR}

clean:
	rm -rf ${BIN_DIR}
