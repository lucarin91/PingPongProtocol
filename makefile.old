CXX = g++
CXXFLAGS = -g -std=c++11 -O3
LCONF = -lconfig++

.PHONY: all_build build clean

all_build: build main_v1.out main_v2.out main_v3.out main_statistics_v1.out main_statistics_v2.out main_statistics_v3.out

main_v1.out: main.cpp build/TopologyGen.o build/Peer.o build/Peer_p.o build/Peer_pp.o build/Message.o build/Logger.o build/ArgsParser.o
	$(CXX) $^ $(CXXFLAGS) $(LCONF) -DV1 -o $@

main_v2.out: main.cpp build/TopologyGen.o build/Peer.o build/Peer_p.o build/Peer_pp.o build/Message.o build/Logger.o build/ArgsParser.o
	$(CXX) $^ $(CXXFLAGS) $(LCONF) -DV2 -o $@

main_v3.out: main.cpp build/TopologyGen.o build/Peer.o build/Peer_p.o build/Peer_pp.o build/Message.o build/Logger.o build/ArgsParser.o
	$(CXX) $^ $(CXXFLAGS) $(LCONF) -DV3 -o $@

main_statistics_v1.out: main_statistics.cpp build/TopologyGen.o build/Peer.o build/Peer_p.o build/Peer_pp.o build/Message.o build/Logger.o build/ArgsParser.o
	$(CXX) $^ $(CXXFLAGS) $(LCONF) -DV1 -o $@

main_statistics_v2.out: main_statistics.cpp build/TopologyGen.o build/Peer.o build/Peer_p.o build/Peer_pp.o build/Message.o build/Logger.o build/ArgsParser.o
	$(CXX) $^ $(CXXFLAGS) $(LCONF) -DV2 -o $@

main_statistics_v3.out: main_statistics.cpp build/TopologyGen.o build/Peer.o build/Peer_p.o build/Peer_pp.o build/Message.o build/Logger.o build/ArgsParser.o
	$(CXX) $^ $(CXXFLAGS) $(LCONF) -DV3 -o $@

build/%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

build:
	mkdir -p build

clean:
	rm -Rvf build main.out
