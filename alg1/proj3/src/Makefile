all: main.o auxiliar.o colecao.o test.o
	gcc main.o auxiliar.o colecao.o -o programa 
	gcc test.o auxiliar.o colecao.o -o test
main.o: main.c
	gcc -g main.c -c
auxiliar.o: auxiliar.c
	gcc auxiliar.c -c
colecao.o: colecao.c
	gcc -g colecao.c -c 
test.o:
	gcc -g test.c -c
run:
	./programa
clean:
	rm -rf test programa *.o
