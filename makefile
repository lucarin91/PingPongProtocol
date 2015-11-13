all: build main.cpp
	g++ -g -std=c++11 main.cpp Message.cpp Peer.cpp  -o main.out

build:
	mkdir -p build

clean:
	rm -Rfv build *.gch main.out
