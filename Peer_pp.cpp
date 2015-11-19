#include "Peer_pp.hpp"

using namespace std;

void Peer_pp::initTimer(){
  addTimer([]()->int{return 60;},[&](time_t now) -> void {
    //time_t elapse = 30;
    log("FILTER PONG CACHE");
    for (auto p = this->timeList.begin(); p != this->timeList.end();) {
      if (p->tstamp <= now){
        log("\tremoved"+(*p).toString());
        this->pongCache[p->neighbor_id].erase(p->original_sender);
        p = this->timeList.erase(p);
      }else{
        log("\tmantened"+p->toString());
        ++p;
      }
    }
  });
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
  Peer_p::addPongCache(neighbor, m);
  this->timeList.emplace(this->timeList.end(),time(0)+Peer_pp::CACHE_TIME, m.originalSender, m.lastSender);
}
