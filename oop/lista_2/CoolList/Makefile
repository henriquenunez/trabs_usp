
all: clean build_dir build run


build_dir:
	#mkdir ./bin

build:
	#javac -source 8 -target 1.8 EntradaTeclado.java -d .
	javac -source 8 -target 1.8 *.java -d .

run:
	java coollist.CoolList

clean:
	rm -rf ./bin || true
	rm -rf entradateclado || true
	rm -rf coollist || true

