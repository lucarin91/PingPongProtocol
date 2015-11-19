#include "Peer_p.hpp"

using namespace std;

Peer_p::Peer_p(int               uid,
               shared_ptr<Logger>logger) : Peer(uid, logger) {
  initTimer();
}

Peer_p::Peer_p(shared_ptr<Logger>logger) : Peer(logger) {
  initTimer();
}

Peer_p::Peer_p() : Peer(nullptr) {
  initTimer();
}

void Peer_p::initTimer() {
  addTimer([]()->int{return rand()%10+2;}, [&](time_t)->void {
    log("send Pings...");
    sendPing();
  });
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

  log("\tadd PONG to the cache", m);
  auto got = this->pongCache.find(neighbor);
  if (got != this->pongCache.end()) {
    log("\tadd to existing list",  m);
    got->second.emplace(m.originalSender,unique_ptr<Message>(new Message(m)));
  } else {
    log("\tcreate a new list",     m);
    unordered_map< int, unique_ptr<Message> > map;
    map.emplace(m.originalSender,unique_ptr<Message>(new Message(m)));
    this->pongCache.emplace(neighbor, move(map));
  }
}

void Peer_p::sendChachedPong(int to, const Message& m) {
  for (auto& n : this->neighbor) {
    if (n.first != to) {
      auto got = this->pongCache.find(n.first);

      if (got != this->pongCache.end()) {
        for (auto& pong : got->second) {
          log("\treply with cached PONG!", *pong.second);
          forwordOne(new Message(m.id, MsgType::PONG, pong.second->originalSender,
                                 getUID()), to);
        }
      } else {
        log("\tforword PING!", m);
        n.second->putMessage(new Message(m));
      }
    }
  }
}
