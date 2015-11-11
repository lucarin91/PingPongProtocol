#ifndef Peer_h_
#define Peer_h_

#include <iostream>
#include <vector>
#include <unordered_map>
#include "Message.hpp"

class Peer{
public:
  Peer(int uid) : UID(uid) {};
  void putMessage(Message);
  void doWork(int);
  int getUID() {return UID;}
  void addNeighbor(const Peer&);

private:
  int UID;
  std::vector<Peer*> neighbor;
  //std::unordered_map<int, *Peer> pingTable;
};
#endif
