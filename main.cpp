#include <iostream>
#include <vector>
#include "Peer.hpp"
using namespace std;

int main (int argc, char* argv[]){
  srand(time(0));
  std::cout << "Ping <--> Pong" << std::endl;

  Peer p1(1),p2(2);
  p1.addNeighbor(p2);
  p2.addNeighbor(p1);

  std::vector<Peer> peerVector;
  peerVector.push_back(p1);
  peerVector.push_back(p2);

  while (true){
    for (Peer &p : peerVector){
      p.doWork(0);
    }
  }

  return 0;
}
