CC=gcc
INCLUDE=./
BUILD=/
FLAGS=-Wall
all: main.o list.o student.o
		
debug:
	${CC} -g main.c student.c list.c -o lust ${FLAGS} 
list_debug:
	${CC} -g list_test_main.c list.c -o list ${FLAGS} 
list_debug:
main.o:
	${CC} -c main.c -o main.o
list.o:
	${CC} -c list.c -o list.o
student.o:
	${CC} -c student.c -o student.o
