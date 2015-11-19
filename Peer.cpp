#include "Peer.hpp"

using namespace std;
int Peer::MASTER_ID = 0;

Peer::Peer(int               uid,
           shared_ptr<Logger>logger) : UID(uid), logger(logger) {}

Peer::Peer(shared_ptr<Logger>logger) : Peer(++Peer::MASTER_ID, logger) {}

Peer::Peer() : Peer(nullptr) {}

bool Peer::addNeighbor(Peer& p) {
  auto got = this->neighbor.find(p.getUID());

  if ((this->UID != p.UID) && (got == this->neighbor.end())) {
    this->neighbor.emplace(p.getUID(), &p);
    p.neighbor.emplace(this->UID, this);
    return true;
  } else return false;
}

void Peer::setLogger(shared_ptr<Logger>l) {
  this->logger = l;
}

void Peer::putMessage(Message *m) {
  this->queue.push(m);

  // cout << "peer " << this->UID <<" :: "<< "add to queue" <<
  // this->queue.empty() <<endl;
}

void Peer::checkTimers() {
  time_t now = time(0);

  for (auto p = this->timers.begin(); p != this->timers.end();) {
    log("check timer");
    if (now == p->first) {
      log("timer elapse");
      p->second(now);
      this->timers.erase(p);
    } else ++p;
  }
}

void Peer::addTimer(time_t sec, function<void(time_t)>f) {
  log("add timer "+to_string(sec));
  this->timers.emplace(time(0) + sec, f);
}

void Peer::onValidPing(Message& msg, int sender) {
  if (sender != getUID()) {
    forwordAll(&msg, sender);
    forwordOne(new Message(msg.id, MsgType::PONG, getUID()), sender);
  } else {
    delete &msg;
  }
}

void Peer::onValidPong(Message& msg, int sender) {
  if (sender != getUID()) {
    forwordOne(&msg, sender);
  } else {
    delete &msg;
  }
}

void Peer::onErrorMsg(Message& msg, ErrorType error, int) {
  switch (error) {
  case ErrorType::ALREADY_FORWARDED_PING:
    break;

  case ErrorType::EXPIRED_MSG:
    break;

  case ErrorType::UNOKNOW_PONG:
    break;
  }
  delete &msg;
}

void Peer::onWork() {}

void Peer::work(int quanto) {
  checkTimers();
  onWork();

  // WORK
  for (int i = 0; i < quanto; ++i) {
    if (this->queue.size() > 0) {
      Message *msg = this->queue.front();
      this->queue.pop();
      int sender = msg->lastSender;
      msg->lastSender = this->UID;
      msg->TTL--;
      msg->HOPS++;

      auto got = this->pingTable.find(msg->id);

      if (msg->TTL > 0) {
        switch (msg->type) {
        case MsgType::PING:

          if (got == this->pingTable.end()) {
            log("received valid msg", *msg);
            this->pingTable.emplace(msg->id, sender);
            onValidPing(*msg, sender);
          } else if (got->second != -1) {
            log("discarted already foorword this PING", *msg);
            onErrorMsg(*msg, ErrorType::ALREADY_FORWARDED_PING, sender);
          } else {
            log("discarted is my PING!", *msg);
            onValidPing(*msg, sender);
          }
          break;

        case MsgType::PONG:

          if (got != this->pingTable.end()) {
            if (got->second != -1) {
              log("received valid msg", *msg);
              onValidPong(*msg, sender);
            } else {
              log("received my PONG!", *msg);
              onValidPong(*msg, sender);
            }
          } else {
            log("error: PONG doesn't found in pingTable", *msg);
            onErrorMsg(*msg, ErrorType::UNOKNOW_PONG, sender);
          }
          break;
        }
      } else {
        log("message discarded!", *msg);
        onErrorMsg(*msg, ErrorType::EXPIRED_MSG, sender);
      }
    }
  }
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
