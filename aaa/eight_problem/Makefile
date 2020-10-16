CXX=g++
CXXFLAGS=-std=c++11
LDFLAGS=-fsanitize=address
PROGNAME=eight_problem

all:
	${CXX} ${CXXFLAGS} ${PROGNAME}.cpp -o ${PROGNAME} ${LDFLAGS}

debug:
	${CXX} -g -DDEBUG ${PROGNAME}.cpp -o ${PROGNAME} ${LDFLAGS}

tests:
	./${PROGNAME} < casos/1.in

run:
	@./${PROGNAME}

zip:
	zip ../${PROGNAME}.zip *

