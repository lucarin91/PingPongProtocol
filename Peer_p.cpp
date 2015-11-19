#include "Peer_p.hpp"

using namespace std;

// void Peer_p::initTimer() {
//   function<void(time_t)> f = [&](time_t) -> void {
//                                log("send Pings...");
//                                sendPing();
//                                addTimer(3, f);
//                              };
//   addTimer(3, f);
// }

void Peer_p::initTimer() {
  log("send Pings...");
  sendPing();
  addTimer(3, initTimer);
}

Peer_p::Peer_p(int uid, shared_ptr<Logger>logger) : Peer(uid, logger) {
  addTimer(3, initTimer);
}

Peer_p::Peer_p(shared_ptr<Logger>logger) : Peer(logger) {
  initTimer();
}

Peer_p::Peer_p() : Peer(nullptr) {
  initTimer();
}

void Peer_p::onValidPing(Message& msg, int sender) {
  if (sender != getUID()) {
    forwordOne(new Message(msg.id, MsgType::PONG, getUID()), sender);
    sendChachedPong(sender, msg);
  } else {
    delete &msg;
  }
}

void Peer_p::onValidPong(Message& msg, int sender) {
  if (sender != getUID()) {
    addPongCache(sender, msg);
    forwordOne(&msg, sender);
  } else {
    delete &msg;
  }
}

void Peer_p::addPongCache(int neighbor, const Message& m) {
  auto got = this->pongCache.find(neighbor);

  log("\tadd PONG to the cache", m);

  if (got != this->pongCache.end()) {
    log("\tadd to existing list", m);
    got->second.push_back(unique_ptr<Message>(new Message(m)));
  } else {
    log("\tcreate a new list", m);
    vector<unique_ptr<Message> > v;
    v.push_back(unique_ptr<Message>(new Message(m)));
    this->pongCache.emplace(neighbor, move(v));
  }
}

void Peer_p::sendChachedPong(int to, const Message& m) {
  for (auto& n : this->neighbor) {
    if (n.first != to) {
      auto got = this->pongCache.find(n.first);

      if (got != this->pongCache.end()) {
        for (auto& pong : got->second) {
          log("\treply with cached PONG!", *pong);
          forwordOne(new Message(m.id, MsgType::PONG, pong->originalSender,
                                 getUID()), to);
        }
      } else {
        log("\tforword PING!", m);
        n.second->putMessage(new Message(m));
      }
    }
  }
}
