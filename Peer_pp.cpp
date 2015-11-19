#include "Peer_pp.hpp"

using namespace std;

void Peer_pp::initTimer(){
  function<void(time_t)> f = [&](time_t now) -> void {
    time_t elapse = 30;
    log("FILTER PONG CACHE");
    for (auto p = this->timeList.begin(); p != this->timeList.end();) {
      this->pongCache[(*p).neighbor_id].erase((*p).msg_id);

      if ((*p).tstamp < now - elapse){
        log("\tremoved"+(*p).toString());
        p = this->timeList.erase(p);
      }else{
        log("\tmantened"+(*p).toString());
        ++p;
      }
    }
    addTimer(60,f);
  };
  addTimer(60,f);
}

Peer_pp::Peer_pp(int uid, shared_ptr<Logger>logger) : Peer_p(uid, logger) {initTimer();}

Peer_pp::Peer_pp(shared_ptr<Logger>logger) : Peer_p(logger) {initTimer();}

Peer_pp::Peer_pp() : Peer_p() {initTimer();}


void Peer_pp::sendChachedPong(int to, const Message& m) {
  for (auto& n : this->neighbor) {
    if (n.first != to) {
      auto got = this->pongCache.find(n.first);

      if ((got != this->pongCache.end()) && (got->second.size() > Peer_pp::K)) {
        for (auto& tuple : got->second) {
          log("\treply with cached PONG!", *tuple.second);
          forwordOne(new Message(m.id, MsgType::PONG,
                                 tuple.second->originalSender,
                                 getUID()), to);
        }
        delete &m;
      } else {
        log("\tforword PING!", m);
        n.second->putMessage(new Message(m));
      }
    }
  }
}

void Peer_pp::addPongCache(int neighbor, const Message& m) {
  auto got = this->pongCache.find(neighbor);

  log("\tadd PONG to the cache", m);

  if (got != this->pongCache.end()) {
    log("\tadd to existing map", m);
    got->second.emplace(m.id, unique_ptr<Message>(new Message(m)));
  } else {
    log("\tcreate a new map", m);
    unordered_map<int, unique_ptr<Message> > map;
    map.emplace(m.id, unique_ptr<Message>(new Message(m)));
    this->pongCache.emplace(neighbor, move(map));
  }
  log("\tadd to timeList");
  this->timeList.emplace(this->timeList.end(),time(0), m.id, m.lastSender);
}
