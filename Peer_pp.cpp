#include "Peer_pp.hpp"

using namespace std;

Peer_pp::Peer_pp(int uid, shared_ptr<Logger>logger) : Peer(uid, logger) {}

Peer_pp::Peer_pp(shared_ptr<Logger>logger) : Peer(logger) {}

Peer_pp::Peer_pp() : Peer() {}

void Peer_pp::work(int quanto) {
  // Send Ping
  afterSecond(3, [&]() -> void {
    log("send Pings...");
    sendPing();
  });

  afterSecond(8, [&]() -> void {


    if (!this->timeHeap.empty()) {
      log("filter PONG cache");
      HeapNode p = *this->timeHeap.top();

      while (!this->timeHeap.empty() && p.time > time(0) - 8) {
        this->timeHeap.pop();
        this->pongCache[p.neighbor_id].erase(p.msg_id);
        p = *this->timeHeap.top();
      }
    }
  });

  // WORK
  doWork(quanto, [&]() -> void {
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

void Peer_pp::sendChachedPong(int to, Message& m) {
  for (auto& n : this->neighbor) {
    if (n.first != to) {
      auto got = this->pongCache.find(n.first);

      if ((got != this->pongCache.end()) && (got->second.size() > Peer_pp::K)) {
        for (auto& tuple : got->second) {
          log("\treply with cached PONG!", *tuple.second);
          forwordOne(new Message(m.id, MsgType::PONG,
                                 tuple.second->originalSender,
                                 this->UID), to);
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
  log("\tadd to timeHeap");
  this->timeHeap.push(unique_ptr<HeapNode>(new HeapNode(time(0), m.id,
                                                        m.lastSender)));
}
