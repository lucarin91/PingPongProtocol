#ifndef Peer_p_h_
#define Peer_p_h_

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <memory>
#include <time.h>
#include <string>
#include <cmath>
#include "Peer.hpp"
#include "Message.hpp"
#include "Logger.hpp"

using namespace std;

class Peer_p : public Peer {
  void initTimer();

public:

  Peer_p(const Peer_p&)            = delete;
  Peer_p& operator=(const Peer_p&) = delete;
  Peer_p(Peer_p &&)                = delete;

  Peer_p();
  Peer_p(int uid,
         shared_ptr<Logger>);
  Peer_p(shared_ptr<Logger>);
  ~Peer_p(){}

protected:

  void         onValidPing(unique_ptr<Message>,
                           int) override;
  void         onValidPong(unique_ptr<Message>,
                           int) override;

  virtual bool addPongCache(int,
                            unique_ptr<Message>);
  virtual void sendChachedPong(int,
                               unique_ptr<Message>);
  std::unordered_map<int,//neighbor id
                    std::unordered_map<int,//original sender
                                       unique_ptr<Message>>> pongCache;

};
#endif // ifndef Peer_p_h_
