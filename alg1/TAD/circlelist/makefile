all: circlelist.o main.o
	gcc main.c circlelist.o -o list 

debug: circlelist.o main.o
	gcc -O0 -g main.c circlelist.o -o list 

main.o: main.c
	gcc -g -c main.c

circlelist.o:
	gcc -O0 -g -c circlelist.c -o circlelist.o

run:
	./list
