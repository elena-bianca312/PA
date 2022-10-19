.phony: build clean

build: poduri adrese lego retea

poduri: poduri.cpp
	g++ -g -o poduri poduri.cpp

adrese: adrese.cpp
	g++ -g -o adrese adrese.cpp

lego: lego.cpp
	g++ -g -o lego lego.cpp

retea: retea.cpp
	g++ -g -o retea retea.cpp

run-p1: poduri
	./poduri

run-p2: adrese
	./adrese

run-p3: lego
	./lego

run-p4: retea
	./retea

clean:
	rm -f poduri adrese lego retea
