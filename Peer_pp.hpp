#ifndef Peer_pp_h_
#define Peer_pp_h_

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <memory>
#include <time.h>
#include <string>
#include <cmath>
#include "Peer.hpp"
#include "Peer_p.hpp"

#include "Message.hpp"
#include "Logger.hpp"

using namespace std;

struct ListNode {
  time_t tstamp;
  int    original_sender;
  int    neighbor_id;
  int    msg_id;
  ListNode(time_t tstamp,
           int    original_sender,
           int    neighbor_id,
           int    msg_id) :
    tstamp(tstamp),
    original_sender(original_sender),
    neighbor_id(neighbor_id),
    msg_id(msg_id) {}

  bool operator<(const ListNode& b) {
    return this->tstamp < b.tstamp;
  }

  bool operator>(const ListNode& b) {
    return this->tstamp > b.tstamp;
  }

  string toString() {
    ostringstream stream;

    stream << "time: " << this->tstamp - time(0) << " msg_id: " << msg_id <<" original_sender: " <<
    original_sender <<
    " neighbor_id: " <<  neighbor_id;
    return stream.str();
  }
};

class Peer_pp : public Peer_p {
  static const int K          = 3;
  static const int CACHE_TIME = 60;

  // unordered_map<int, unordered_map<int, unique_ptr<Message> > > pongCache;
  list<ListNode> timeList;

  void initTimerTEST();

public:

  Peer_pp(const Peer_pp&)            = delete;
  Peer_pp& operator=(const Peer_pp&) = delete;
  Peer_pp(Peer_pp &&)                = delete;

  Peer_pp();
  Peer_pp(int uid,
          shared_ptr<Logger>);
  Peer_pp(shared_ptr<Logger>);
  ~Peer_pp() {}

protected:

  //
  // void onValidPing(Message&,
  //                  int) override;
  // void onValidPong(Message&,
  //                  int) override;

  bool addPongCache(int,
                    unique_ptr<Message>) override;
  void sendChachedPong(int,
                       unique_ptr<Message>) override;
};
#endif // ifndef Peer_pp_h_
