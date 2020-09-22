CXX=g++
CXXFLAGS=-g -std=c++11
LDFLAGS=#-fsanitize=address
PROGNAME=ratina_mase

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

