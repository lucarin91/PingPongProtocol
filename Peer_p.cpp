#include "Peer_p.hpp"

using namespace std;

Peer_p::Peer_p(int uid, shared_ptr<Logger>logger) : Peer(uid,logger) {
}

Peer_p::Peer_p(shared_ptr<Logger>logger) : Peer(logger) {}

Peer_p::Peer_p() : Peer(nullptr) {}

void Peer_p::work(int quanto) {
  // Send Ping
  afterSecond(3, [&](time_t) -> void {
    log("send Pings...");
    sendPing();
  });

  // WORK
  doWork(quanto, [&]()->void {
    if (this->queue.size() > 0) {
      Message *msg = this->queue.front();
      this->queue.pop();
      int sender = msg->lastSender;
      msg->TTL--;
      msg->HOPS++;

      auto got = this->pingTable.find(msg->id);

      if (msg->TTL > 0) {
        switch (msg->type) {
        case MsgType::PING:
          if (got == this->pingTable.end()) {
            log("received valid msg", *msg);

            this->pingTable.emplace(msg->id, sender);
            forwordOne(new Message(msg->id, MsgType::PONG, this->UID), sender);

            msg->lastSender = this->UID;
            sendChachedPong(sender, *msg);
          } else if (got->second != -1) {
            log("discarted already foorword this PING", *msg);
          } else {
            log("discarted is my PING!", *msg);
            delete msg;
          }
          break;

        case MsgType::PONG:

          if (got != this->pingTable.end()) {
            if (got->second != -1) {
              // this->pingTable.erase(got->first);
              log("received valid msg", *msg);
              msg->lastSender = this->UID;
              addPongCache(sender, *msg);
              forwordOne(msg, got->second);
            } else {
              log("received my PONG!", *msg);
              delete msg;
            }
          } else {
            log("error: PONG doesn't found in pingTable", *msg);
            delete msg;
          }
          break;
        }
      } else {
        log("message discarded!", *msg);
        delete msg;
      }
    }
  });
}

void Peer_p::addPongCache(int neighbor, const Message& m){
  auto got = this->pongCache.find(neighbor);
  log ("\tadd PONG to the cache", m);
  if (got != this->pongCache.end()){
    log ("\tadd to existing list", m);
    got->second.push_back(unique_ptr<Message>(new Message(m)));
  }else{
    log ("\tcreate a new list", m);
    vector<unique_ptr<Message>> v;
    v.push_back(unique_ptr<Message>(new Message(m)));
    this->pongCache.emplace(neighbor, move(v));
  }
}

void Peer_p::sendChachedPong(int to, const Message& m){
  for (auto& n : this->neighbor) {
    if ( n.first != to){
      auto got = this->pongCache.find(n.first);
      if (got != this->pongCache.end()){
        for(auto& pong : got->second){
          log("\treply with cached PONG!", *pong);
          forwordOne(new Message(m.id, MsgType::PONG, pong->originalSender, this->UID), to);
        }
      }else{
        log("\tforword PING!", m);
        n.second->putMessage(new Message(m));
      }
    }
  }
}
