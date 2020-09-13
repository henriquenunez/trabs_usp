CXX=g++
CXXFLAGS=-g
LDFLAGS=

all:
	${CXX} coin_collector.cpp -o coin_collector

debug:
	${CXX} -DDEBUG coin_collector.cpp -o coin_collector

tests:
	./coin_collector < casos/1.in

run:
	./coin_collector

zip:
	zip ../coin_collector.zip *
