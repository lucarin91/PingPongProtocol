CXX = g++
CXXFLAGS = -g -std=c++11 -O3

.PHONY: all_build build clean

all_build: build main.out

../build/%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
