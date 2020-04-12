build:
	javac Random.java Placar.java Dado.java RolaDados.java Bozo.java\
 EntradaTeclado.java -d .
tests:
	javac TestPlacar.java
	java TestPlacar
	javac TestDado.java
	java TestDado
	javac TestRolaDados.java
	java TestRolaDados

clean_tests:
	rm *.class

all: build tests clean_tests

bozo: build
	java bozo.Bozo

clean:
	rm -r bozo

zip:
	zip ../src.zip ../src/*
