build: tmp main.cpp tmp/TopologyGen.o tmp/Peer.o tmp/Peer_p.o tmp/Peer_pp.o tmp/Message.o tmp/Logger.o
	g++ -g -std=c++11 main.cpp tmp/TopologyGen.o tmp/Peer.o tmp/Peer_p.o tmp/Peer_pp.o tmp/Message.o tmp/Logger.o -lconfig++ -o main.out

tmp/TopologyGen.o: TopologyGen.cpp TopologyGen.hpp
	g++ -c -std=c++11 TopologyGen.cpp -o tmp/TopologyGen.o

tmp/Peer_pp.o: Peer_pp.cpp Peer_pp.hpp
	g++ -c Peer_pp.cpp -std=c++11 -o tmp/Peer_pp.o

tmp/Peer_p.o: Peer_p.cpp Peer_p.hpp
	g++ -g -c -std=c++11 Peer_p.cpp -o tmp/Peer_p.o

tmp/Peer.o: Peer.cpp Peer.hpp
	g++ -g -c -std=c++11 Peer.cpp -o tmp/Peer.o

tmp/Message.o: Message.cpp Message.hpp
	g++ -g -c -std=c++11 Message.cpp -o tmp/Message.o

tmp/Logger.o: Logger.cpp Logger.hpp
	g++ -g -c -std=c++11 Logger.cpp -o tmp/Logger.o

tmp:
	mkdir -p tmp

clean:
	rm -Rfv tmp *.gch main.out
