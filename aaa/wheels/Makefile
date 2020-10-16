all:
	g++ -g wheels.cpp -std=c++11 -O3 -o wheels

run:
	./wheels
zip: clean
	zip ../wheels.zip *

clean:
	rm wheels || true
