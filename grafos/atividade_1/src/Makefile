
all: clean build_dir graph.o tests
	gcc -g main.c ./bin/graph.o -o ./bin/graph_poc

build_dir:
	mkdir ./bin

graph.o:
	gcc -c graph.c -o ./bin/graph.o

clean:
	rm -rf ./bin

tests:
	gcc testA.c ./bin/graph.o -o ./bin/test_a
	gcc testB.c ./bin/graph.o -o ./bin/test_b

run:
	./bin/graph_poc

zip: clean
	zip ../src.zip *
