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

enum class ErrorType { ALREADY_FORWARDED_PING, UNOKNOW_PONG, EXPIRED_MSG };


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

  typedef typename std::unordered_map<int, Peer *>::iterator       iterator;
  typedef typename std::unordered_map<int, Peer *>::const_iterator const_iterator;

  iterator begin() {
    return neighbor.begin();
  }

  const_iterator begin() const {
    return neighbor.begin();
  }

  const_iterator cbegin() const {
    return neighbor.cbegin();
  }

  iterator end() {
    return neighbor.end();
  }

  const_iterator end() const {
    return neighbor.end();
  }

  const_iterator cend() const {
    return neighbor.cend();
  }

protected:

  int UID;
  std::unordered_map<int, Peer *> neighbor;
  std::unordered_map<int, int>    pingTable;
  std::queue<Message *> queue;
  time_t lastTime;
  static int MASTER_ID;
  shared_ptr<Logger> logger;
  void afterSecond(int,function<void(time_t)>);
  void doWork(int,
              function<void()>);
  void log(string);
  void log(string, const Message &m);

  void Peer::onValidPing(Message&, bool);
  void Peer::onValidPong(Message&, bool);
  void Peer::onErrorMsg(Message&,ErrorType);

};
#endif // ifndef Peer_h_
