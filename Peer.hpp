#ifndef Peer_h_
#define Peer_h_

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <time.h>
#include "Message.hpp"

class Peer {
public:

  Peer(int uid) : UID(uid), lastTime(time(0)) {}

  void putMessage(const Message&);
  void doWork(int);
  int  getUID() const {
    return UID;
  }

  void addNeighbor(const Peer&);

private:

  int UID;
  std::vector<Peer> neighbor;
  std::unordered_map<int, Peer *> pingTable;
  std::queue<Message> queue;
  time_t lastTime;
};
#endif // ifndef Peer_h_
