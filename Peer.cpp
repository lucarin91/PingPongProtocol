#include <iostream>
#include <cmath>
#include "Peer.hpp"
#include <time.h>

using namespace std;

Peer::Peer(int id) : UID(id){
  this->lastTime = time(0)+floor(rand() % 5);
  // cout << this->UID <<" "<< this->lastTime << endl;
}

void Peer::addNeighbor(const Peer& p){
  this->neighbor.push_back(p);
}

void Peer::putMessage(const Message& m){
  this->queue.push(m);
}

void Peer::doWork(int quanto){
  time_t now = time(0);
  if (difftime(now, this->lastTime) > 2){
    cout << "pear "<< this->UID <<" after 2 second" << endl;
    sendPing();
    this->lastTime = now;
  }
  for (int i=0; i<quanto; ++i){
    cout << "pear " << this->UID <<" same work! "<<endl;
    MessageWrapper m = this->queue.front();
    if (m.msg.type == MsgType.PING){

    }else if (m.msg.type == MsgType.PONG){

    }
  }

}

void Peer::sendPing(){
  for (Peer &p : this->neighbor){
    Message m (floor(rand()%100), MsgType::PING, 4, 0);
    p.putMessage(m);
  }
}
