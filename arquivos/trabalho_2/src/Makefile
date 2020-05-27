CFLAGS = -g
LDFLAGS = -fsanitize=address
BIN_DIR = ./bin

all: clean build

build: build_dir csv.o bin.o newborns.o
	gcc ${CFLAGS} ./bin/csv.o ./bin/bin.o ./bin/newborns.o main.c -o ${BIN_DIR}/trab ${LDFLAGS}

csv.o: build_dir
	gcc ${CFLAGS} -c csv.c -o ${BIN_DIR}/csv.o ${LDFLAGS}

bin.o: build_dir
	gcc ${CFLAGS} -c bin.c -o ${BIN_DIR}/bin.o ${LDFLAGS}

newborns.o: build_dir
	gcc ${CFLAGS} -c newborns.c -o ${BIN_DIR}/newborns.o ${LDFLAGS}

build_tests: clean csv.o bin.o newborns.o
	gcc ${CFLAGS} testcsvreader.c ${BIN_DIR}/csv.o -o ${BIN_DIR}/testcsvreader ${LDFLAGS}
	gcc ${CFLAGS} testbin.c ${BIN_DIR}/bin.o -o ${BIN_DIR}/testbin ${LDFLAGS}
	gcc ${CFLAGS} testnb.c ${BIN_DIR}/newborns.o ${BIN_DIR}/csv.o ${BIN_DIR}/bin.o -o ${BIN_DIR}/testnb ${LDFLAGS}
	gcc ${CFLAGS} testdelete.c ${BIN_DIR}/bin.o -o ${BIN_DIR}/testdelete ${LDFLAGS}

test_csv: build_tests
	${BIN_DIR}/testcsvreader

test_bin: build_tests
	${BIN_DIR}/testbin

test_newborns: build_tests
	${BIN_DIR}/testnb

test_deletion: build_tests
	cp small_test_bin.bin ${BIN_DIR}/delete.bin
	${BIN_DIR}/testdelete

tests: test_csv test_bin test_newborns

run:
	${BIN_DIR}/trab
	rm *.bin || true

zip: clean
	rm *.bin || true
	zip ../src.zip *

build_dir:
	mkdir ${BIN_DIR} || true

clean:
	rm -rf ${BIN_DIR}
