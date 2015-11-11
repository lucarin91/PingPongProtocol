#include <iostream>
#include <vector>
#include "Peer.hpp"

int main (int argc, char* argv[]){
  std::cout << "Ping <--> Pong" << std::endl;

  Peer p1(1),p2(2);

  std::vector<Peer> peerVector;
  p1.addNeighbor(p2);
  peerVector.push_back(p1);

  p2.addNeighbor(p1);
  peerVector.push_back(p2);

  for (Peer p : peerVector){
    p.doWork(2);
  }

  return 0;
}
