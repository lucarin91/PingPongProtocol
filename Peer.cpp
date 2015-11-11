#include <iostream>
#include "Peer.hpp"

void Peer::addNeighbor(Peer& p){
  this->neighbor.push_back(*p);
}

void Peer::doWork(int time){
  for (int i=0; i<time; ++i)
    std::cout << "work! "<<std::endl;
}
