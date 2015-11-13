#include <iostream>
#include <vector>
#include <unistd.h>
#include "Peer.hpp"

using namespace std;

int main (int argc, char* argv[]){
  srand(time(0));
  std::cout << "Ping <--> Pong" << std::endl;
  Peer p1,p2,p3,p4;
  p1.addNeighbor(p2);
  p1.addNeighbor(p3);
  p2.addNeighbor(p4);
  p2.addNeighbor(p3);
  // p2.addNeighbor(p1);

  std::vector<Peer> peerVector;
  peerVector.push_back(p1);
  peerVector.push_back(p2);

  while (true){
    p1.doWork(1);
    p2.doWork(1);
    p3.doWork(1);
    p4.doWork(1);
    sleep(1);
    // for (int i = 0; i < peerVector.size(); i++){
    //   peerVector[i].doWork(1);
    //   sleep(1);
    // }
  }

  return 0;
}
