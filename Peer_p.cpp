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
  addTimer([]()->int{return rand()%25+5;}, [&](time_t)->void {
    log("send Pings...");
    sendPing();
  });
}

void Peer_p::onValidPing(unique_ptr<Message> msg, int sender) {
    forwordOne(unique_ptr<Message>(new Message(msg->id, MsgType::PONG, getUID())), sender);
    sendChachedPong(sender, move(msg));
}

void Peer_p::onValidPong(unique_ptr<Message> msg, int sender) {
    addPongCache(sender, unique_ptr<Message>(new Message(*msg)));
    forwordOne(move(msg), sender);
}

bool Peer_p::addPongCache(int neighbor, unique_ptr<Message> m) {

  log("\tadd PONG to the cache", *m);
  auto got = this->pongCache.find(neighbor);
  if (got != this->pongCache.end()) {
    log("\tadd to existing list",  *m);
    unique_ptr<Message> msgPtr (new Message(*m));
    // auto ret = got->second.emplace(m->originalSender, move(msgPtr));
    // log("\tinsertion: "+ to_string(ret.second));
    // if (ret.second)
    got->second[m->originalSender] = move(msgPtr);
    return true;
  } else {
    log("\tcreate a new list",     *m);
    unordered_map< int, unique_ptr<Message> > map;
    map.emplace(m->originalSender,unique_ptr<Message>(new Message(*m)));
    this->pongCache.emplace(neighbor, move(map));
    return true;
  }
}

void Peer_p::sendChachedPong(int to,unique_ptr<Message> m) {
  for (auto& n : this->neighbor) {
    if (n.first != to) {
      auto got = this->pongCache.find(n.first);

      if (got != this->pongCache.end()) {
        for (auto& pong : got->second) {
          log("\treply with cached PONG!", *pong.second);
          forwordOne(unique_ptr<Message>(new Message(m->id, MsgType::PONG, pong.second->originalSender,
                                 getUID())), to);
        }
      } else {
        log("\tforword PING!", *m);
        auto t = n.second.lock();
        t->putMessage(unique_ptr<Message>(new Message(*m)));
      }
    }
  }
  m.reset();
}
