#ifndef Peer_h_
#define Peer_h_

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <memory>
#include <time.h>
#include "Message.hpp"

using namespace std;
class Peer {
public:
  //Peer(const Peer& p) =delete;
  //Peer(const Peer&&) =delete;
  Peer& operator=(const Peer&) =delete;

  //Peer(int uid) : UID(uid), lastTime(time(0)) {}
  Peer();
  void putMessage(Message*);
  void forwordAll(Message*, int);
  void forwordOne(Message*, int);
  void doWork(int);
  int  getUID() const {
    return this->UID;
  }

  void addNeighbor(Peer&);

private:

  int UID;
  //std::vector<Peer> neighbor;
  std::unordered_map<int, Peer*> neighbor;
  std::unordered_map<int, int> pingTable;
  std::queue<Message*> queue;
  time_t lastTime;
  static int masterId;
  void sendPing();
  void log(string);
};
#endif // ifndef Peer_h_
