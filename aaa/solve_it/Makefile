CXX=g++
CXXFLAGS=-O3 -std=c++11 -Wall
LDFLAGS=#-fsanitize=address
PROGNAME=solve_it

all:
	${CXX} ${CXXFLAGS} ${PROGNAME}.cpp -o ${PROGNAME} ${LDFLAGS}

debug:
	${CXX} -g -DDEBUG ${PROGNAME}.cpp -o ${PROGNAME} ${LDFLAGS}

tests:
	./${PROGNAME} < casos/1.in

run:
	./${PROGNAME}

zip:
	zip ../${PROGNAME}.zip *
clean:
	rm ${PROGNAME} || true

