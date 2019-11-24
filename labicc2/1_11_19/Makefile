all: sort
	gcc -O0 -g 1.c *.o -o 1 -fsanitize=address
	gcc -g 2.c *.o -o 2
	gcc -g 3.c *.o -o 3
	gcc -g 4.c *.o -o 4

sort:
	gcc -c -g mergesort.c -o mergesort.o

clean:
	rm -rf *.o 1 2 3 4
