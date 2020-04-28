CFLAGS = -g
LDFLAGS = -fsanitize=address
BIN_DIR = ./bin

all: build

build: build_dir
	gcc ${CFLAGS} main.c -o ${BIN_DIR}/trab ${LDFLAGS}

csv.o: build_dir
	gcc -g -c csv.c -o ${BIN_DIR}/csv.o ${LDFLAGS}

bin.o: build_dir
	gcc -g -c bin.c -o ${BIN_DIR}/bin.o ${LDFLAGS}

build_tests: clean csv.o bin.o
	gcc -g testcsvreader.c ${BIN_DIR}/csv.o -o ${BIN_DIR}/testcsvreader ${LDFLAGS}
	gcc -g testbin.c ${BIN_DIR}/bin.o -o ${BIN_DIR}/testbin ${LDFLAGS}

test_csv: build_tests
	${BIN_DIR}/testcsvreader

test_bin: build_tests
	${BIN_DIR}/testbin

tests: test_csv test_bin

run:
	${BIN_DIR}/trab

zip: clean
	zip ../src.zip *

build_dir:
	mkdir ${BIN_DIR}

clean:
	rm -rf ${BIN_DIR}
