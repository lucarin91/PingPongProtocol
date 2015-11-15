#include "Peer.hpp"

using namespace std;
int Peer::MASTER_ID = 0;

Peer::Peer(int uid, shared_ptr<Logger>logger) : UID(uid), logger(logger) {
  this->lastTime = time(0) + floor(rand() % 20);
  cout << this->UID << " " << this->lastTime << endl;
}

Peer::Peer(shared_ptr<Logger>logger) : Peer(++Peer::MASTER_ID, logger) {}

Peer::Peer() : Peer(nullptr) {}

// Peer::Peer(Peer&& p){
//   this->UID = p.UID;
//   this->neighbor = p.neighbor;
//   this->pingTable = p.pingTable;
//   this->queue = p.queue;
//   this->lastTime = p.lastTime;
//   }

bool Peer::addNeighbor(Peer& p) {
  auto got = this->neighbor.find(p.getUID());
  if (this->UID != p.UID && got == this->neighbor.end()) {
    this->neighbor.emplace(p.getUID(), &p);
    p.neighbor.emplace(this->UID, this);
    return true;
  }else
    return false;
}

void Peer::setLogger(shared_ptr<Logger> l){
    this->logger = l;
}

void Peer::putMessage(Message *m) {
  this->queue.push(m);

  // cout << "peer " << this->UID <<" :: "<< "add to queue" <<
  // this->queue.empty() <<endl;
}

void Peer::afterSecond(int s, function<void()>f) {
  time_t now = time(0);

  if (difftime(now, this->lastTime) > 5) {
    f();
    this->lastTime = now;
  }
}

void Peer::doWork(int quanto, function<void()>f) {
  for (int i = 0; i < quanto; ++i) {
    f();
  }
}

void Peer::work(int quanto) {
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
            msg->lastSender = this->UID;
            this->pingTable.emplace(msg->id, sender);
            forwordAll(msg, sender);
            forwordOne(new Message(msg->id, MsgType::PONG, this->UID), sender);
          } else if (got->second != -1) {
            log("discarted already foorword this PING", *msg);
          } else {
            log("discarted is my PING!", *msg);

            // this->pingTable.erase(got->first);
            delete msg;
          }
          break;

        case MsgType::PONG:

          if (got != this->pingTable.end()) {
            if (got->second != -1) {
              // this->pingTable.erase(got->first);
              log("received valid msg", *msg);
              msg->lastSender = this->UID;
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

void Peer::forwordAll(Message *m, int notSendId) {
  for (auto& p : this->neighbor) {
    if (p.first != notSendId) p.second->putMessage(new Message(*m));
  }
}

void Peer::forwordOne(Message *m, int to) {
  try {
    this->neighbor.at(to)->putMessage(m);
  } catch (out_of_range e) {
    log("Peer not found!");
  }
}

void Peer::sendPing() {
  for (auto& p : this->neighbor) {
    Message *msg = new Message(MsgType::PING, this->UID);
    this->pingTable.emplace(msg->id, -1);
    p.second->putMessage(msg);
  }
}

void Peer::log(string s) {
  if (this->logger != nullptr) this->logger->printLog(this->UID, s);
}

void Peer::log(string s, const Message& m) {
  if (this->logger != nullptr) this->logger->printLog(this->UID, s, m);
}
