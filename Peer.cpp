#include <iostream>
#include <string>
#include <cmath>
#include "Peer.hpp"
#include <time.h>

using namespace std;

Peer::Peer(){
  this->lastTime = time(0)+floor(rand() % 20);
  this->UID = ++Peer::masterId;
  cout << this->UID <<" "<< this->lastTime << endl;
}

int Peer::masterId =0;

void Peer::addNeighbor(Peer& p){
  this->neighbor.emplace(p.getUID(), &p);
  p.neighbor.emplace(this->UID, this);
}

void Peer::putMessage(Message* m){
  this->queue.push( m );
  //cout << "peer " << this->UID <<" :: "<< "add to queue" << this->queue.empty() <<endl;
}

void Peer::doWork(int quanto){
  time_t now = time(0);
  // send PING
  if (difftime(now, this->lastTime) > 5){
    sendPing();
    log("send Ping");
    this->lastTime = now;
  }

  //WORK
  for (int i=0; i<quanto; ++i){
    cout << "peer " << this->UID <<" :: "<< ".........." <<endl;
    if (this->queue.size()>0){
      log("one message!");
      Message* msg = this->queue.front();
      this->queue.pop();
      int sender = msg->sender;
      if (msg->type == MsgType::PING){
        log("received PING");
        this->pingTable.emplace(msg->id, sender);
        msg->TTL--;
        msg->HOPS++;
        msg->sender = this->UID;
        forwordAll(msg, sender);
        forwordOne(new Message (msg->id, MsgType::PONG, 4, 0, this->UID), sender);
      }else if (msg->type == MsgType::PONG){
        log("received PONG");
        msg->TTL--;
        msg->HOPS++;
        msg->sender = this->UID;
        try{
          int to = this->pingTable.at(msg->id);
          cout << "peer " << this->UID <<" :: "<< to <<endl;
          forwordOne(msg, to);
        }catch(out_of_range e){
          log("PONG came home!");
          delete msg;
        }
      }

    }
  }
}

void Peer::forwordAll(Message* m, int notSendId){
  for (auto& p : this->neighbor){
    if (p.first != notSendId)
      p.second->putMessage(new Message(*m));
  }
}

void Peer::forwordOne(Message* m, int to){
  try{
    this->neighbor.at(to)->putMessage(m);
  }catch(out_of_range e){
    std::cout << "Peer not found";
  }
}

void Peer::sendPing(){
  for (auto& p : this->neighbor){
    p.second->putMessage(new Message (floor(rand()%100), MsgType::PING, 4, 0, this->UID));
    cout << "peer " << this->UID <<" :: "<< p.second->getUID() <<endl;
  }
}

void Peer::log(string s){
  cout << "peer " << this->UID <<" :: "<< s <<endl;
}
