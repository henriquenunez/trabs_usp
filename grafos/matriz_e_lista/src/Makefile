
all: clean build_dir graph.o
	gcc -g mat_main.c ./bin/graph.o -o ./bin/mat_poc
	gcc -g list_main.c ./bin/graph.o -o ./bin/list_poc

build_dir:
	mkdir ./bin

graph.o: build_dir
	gcc -g -c graph.c -o ./bin/graph.o

clean:
	rm -rf ./bin

tests:
	gcc testA.c ./bin/graph.o -o ./bin/test_a -fsanitize=address
	gcc testB.c ./bin/graph.o -o ./bin/test_b -fsanitize=address

run:
	./bin/list_poc

zip: clean
	zip ../src.zip *
