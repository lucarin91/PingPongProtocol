all: build main.cpp
	g++ -g -std=c++11 main.cpp Message.cpp Peer.cpp Peer_p.cpp Logger.cpp TopologyGen.cpp -o main.out

build:
	mkdir -p build

clean:
	rm -Rfv build *.gch main.out
