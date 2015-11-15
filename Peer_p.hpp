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
public:

  Peer_p(const Peer_p&)            = delete;
  Peer_p& operator=(const Peer_p&) = delete;
  Peer_p(Peer_p&&)                 = delete;

  Peer_p();
  Peer_p(int uid,
         shared_ptr<Logger>);
  Peer_p(shared_ptr<Logger>);

  void work(int) override;

protected:

  std::unordered_map<int, vector<unique_ptr<Message> > > pongCache;
  void addPongCache(int, const Message&);
  void sendChachedPong(int to, const Message& msg);
};
#endif // ifndef Peer_p_h_
