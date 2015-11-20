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

enum class ErrorType { ALREADY_FORWARDED_PING, UNOKNOW_PONG, EXPIRED_MSG, MY_PING,
                       MY_PONG };

struct TimeStr {
  time_t                now;
  function<int()>       sec;
  function<void(time_t)>fun;
  TimeStr(time_t                now,
          function<int()>       sec,
          function<void(time_t)>fun) : now(now), sec(sec), fun(fun) {}
};

class Peer : public std::enable_shared_from_this<Peer>{
  int UID;
  int lastMsg;
  int allMsg;
  void checkTimers();

  static int MASTER_ID;
  std::queue<unique_ptr<Message>> queue;

  vector<TimeStr> timers;
  shared_ptr<Logger> logger;

  unordered_map<int, int> pingTable;

public:

  Peer(const Peer&)            = delete;
  Peer& operator=(const Peer&) = delete;
  Peer(Peer &&)                = delete;

  Peer();
  Peer(int uid,
       shared_ptr<Logger>);
  Peer(shared_ptr<Logger>);

  void work(int);
  void putMessage(unique_ptr<Message>);
  int  getUID() const {
    return this->UID;
  }

  int  getLastStatistics(){
    int tmp = lastMsg;
    lastMsg=0;
    return tmp;
  }
  int  getAllStatistics(){
    return allMsg;
  }
  void sendPing();
  bool addNeighbor(shared_ptr<Peer>);
  void setLogger(shared_ptr<Logger>);

  typedef typename std::unordered_map<int, weak_ptr<Peer> >::iterator       iterator;
  typedef typename std::unordered_map<int, weak_ptr<Peer> >::const_iterator const_iterator;

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

  void         forwordAll(unique_ptr<Message>, int);
  void         forwordOne(unique_ptr<Message>, int);

  virtual void onValidPing(unique_ptr<Message>, int);
  virtual void onValidPong(unique_ptr<Message>, int);
  virtual void onErrorMsg(unique_ptr<Message>, ErrorType, int);
  virtual void onWork();
  void         addTimer(function<int()>,
                        function<void(time_t)>);

  unordered_map<int, weak_ptr<Peer>> neighbor;


  void log(string s) {
    if (this->logger != nullptr) this->logger->printLog(this->UID, s);
  }

  void log(string s, const Message& m) {
    if (this->logger != nullptr) this->logger->printLog(this->UID, s, m);
  }
  private:
  void incrementNumberMsg(){
    ++allMsg;
    ++lastMsg;
  }
};
#endif // ifndef Peer_h_
