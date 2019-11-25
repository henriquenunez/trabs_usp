all: main.o auxiliar.o colecao.o test.o
	gcc main.o auxiliar.o colecao.o -o programa
	gcc test.o auxiliar.o colecao.o -o test
main.o: main.c
	gcc main.c -c
auxiliar.o: auxiliar.c
	gcc auxiliar.c -c
colecao.o: colecao.c
	gcc colecao.c -c
test.o:
	gcc test.c -c
run:
	./programa
clean:
	rm -rf programa *.o
