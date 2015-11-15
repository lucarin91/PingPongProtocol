#ifndef Peer_pp_h_
#define Peer_pp_h_

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <memory>
#include <time.h>
#include <string>
#include <cmath>
#include "Peer.hpp"
// #include "Peer_p.hpp"
#include "Message.hpp"
#include "Logger.hpp"

using namespace std;

struct HeapNode{
  int time;
  int msg_id;
  int neighbor_id;
  HeapNode(int time, int msg_id, int neightbot_id) : time(time), msg_id(msg_id), neighbor_id(neighbor_id) {}
  bool operator<(const HeapNode& b) {
    return this->time > b.time;
  }
};

class Peer_pp : public Peer {
public:

  Peer_pp(const Peer_pp&)            = delete;
  Peer_pp& operator=(const Peer_pp&) = delete;
  Peer_pp(Peer_pp&&)                 = delete;

  Peer_pp();
  Peer_pp(int uid,
          shared_ptr<Logger>);
  Peer_pp(shared_ptr<Logger>);

  void work(int) override;

protected:
  static const int K = 3;
  unordered_map<int, unordered_map<int, unique_ptr<Message>> > pongCache;
  priority_queue<unique_ptr<HeapNode>> timeHeap;
  void addPongCache(int, const Message&);
  void sendChachedPong(int, Message&);
};
#endif // ifndef Peer_pp_h_
