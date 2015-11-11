#include <iostream>
#include "Peer.hpp"
#include <time.h>

using namespace std;

void Peer::addNeighbor(const Peer& p){
  this->neighbor.push_back(p);
}

void Peer::putMessage(const Message& m){
  this->queue.push(m);
}

void Peer::doWork(int quanto){
  time_t now = time(0);
  //cout <<difftime(now, this->lastTime)<<endl;
  //cout << UID << " " << this->lastTime <<" "<<now<<endl;
  if (difftime(now, this->lastTime) > 2){
    std::cout << "pear "<<UID<<"after 2 second"<<std::endl;
    this->lastTime = now;
    //cout << UID << " "<<this->lastTime <<" "<<now<<endl;
  }
  for (int i=0; i<quanto; ++i)
    std::cout << "pear " <<UID <<" same work! "<<std::endl;
}
