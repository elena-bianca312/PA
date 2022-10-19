.phony: build clean

build: crypto stocks valley ridge trigigel

crypto: crypto.cpp
	g++ -g -o crypto crypto.cpp

stocks: stocks.cpp
	g++ -g -o stocks stocks.cpp

valley: valley.cpp
	g++ -g -o valley valley.cpp

ridge: ridge.cpp
	g++ -g -o ridge ridge.cpp

trigigel: trigigel.cpp
	g++ -g -o trigigel trigigel.cpp

run-p1: crypto
	./crypto

run-p2: stocks
	./stocks

run-p3: valley
	./valley

run-p4: ridge
	./ridge

run-p5: trigigel
	./trigigel

clean:
	rm -f crypto stocks valley ridge trigigel



