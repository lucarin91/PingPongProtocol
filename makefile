all: build main.cpp build/Peer.o build/Message.o
	g++ -g -std=c++11 main.cpp -o main.out

build/Peer.o: Peer.cpp
	g++ -g -c -std=c++11 Peer.cpp -o build/Peer.o


build/Message.o: Message.hpp
		g++ -g -c -std=c++11 Message.hpp -o build/Message.o

build:
	mkdir -p build

clean:
	rm -Rfv build
