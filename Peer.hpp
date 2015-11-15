#ifndef Peer_h_
#define Peer_h_

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <memory>
#include <time.h>
#include <string>
#include <cmath>
#include "Message.hpp"
#include "Logger.hpp"

using namespace std;


class Peer {
public:

  Peer(const Peer&)            = delete;
  Peer& operator=(const Peer&) = delete;
  Peer(Peer&&)                 = delete;

  Peer();
  Peer(int uid,
       shared_ptr<Logger>);
  Peer(shared_ptr<Logger>);

  void         putMessage(Message *);
  void         forwordAll(Message *,
                          int);
  void         forwordOne(Message *,
                          int);
  virtual void work(int);
  int          getUID() const {
    return this->UID;
  }

  void sendPing();
  bool addNeighbor(Peer&);
  void setLogger(shared_ptr<Logger>);

  std::unordered_map<int, Peer *> neighbor;
protected:

  int UID;

  // std::vector<Peer> neighbor;
  std::unordered_map<int, int>    pingTable;
  std::queue<Message *> queue;
  time_t lastTime;
  static int MASTER_ID;
  shared_ptr<Logger> logger;
  void afterSecond(int,
                   function<void()>);
  void doWork(int,
              function<void()>);
  void log(string);
  void log(string, const Message &m);
};
#endif // ifndef Peer_h_
