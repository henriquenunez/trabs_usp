CXX=g++
CXXFLAGS=-std=c++11
LDFLAGS=

all:
	${CXX} ${CXXFLAGS} station_balance.cpp -o station_balance ${LDFLAGS}

debug:
	${CXX} -g -DDEBUG station_balance.cpp -o station_balance ${LDFLAGS}

tests:
	./station_balance < casos/1.in

run:
	./station_balance

zip:
	zip ../station_balance.zip *
