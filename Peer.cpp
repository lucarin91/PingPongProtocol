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
  for (auto& p : this->timers) {
    // log("check timer");
    time_t now = time(0);

    if (now >= p.now) {
      log("timer elapsed..");
      p.fun(now);
      time_t secConst = p.sec();
      p.now = time(0) + secConst;
      log("new timer after: " + to_string(secConst));

      // p = this->timers.erase(p);
    }
  }
}

void Peer::addTimer(function<int()>sec, function<void(time_t)>f) {
  int secCont = sec();

      log("add timer " + to_string(secCont));
  this->timers.push_back(TimeStr(time(0) + secCont, sec, f));
}

void Peer::onValidPing(Message& msg, int sender) {
  forwordAll(&msg, sender);
  forwordOne(new Message(msg.id, MsgType::PONG, getUID()), sender);
}

void Peer::onValidPong(Message& msg, int sender) {
  forwordOne(&msg, sender);
}

void Peer::onErrorMsg(Message& msg, ErrorType error, int) {
  switch (error) {
  case ErrorType::MY_PING:
    break;

  case ErrorType::MY_PONG:
    break;

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
            onValidPing(*msg, sender);
          } else if (got->second != -1) {
            log("discarted already foorword this PING", *msg);
            msg->lastSender = this->UID;
            onErrorMsg(*msg, ErrorType::ALREADY_FORWARDED_PING, sender);
          } else {
            log("discarted is my PING!", *msg);
            msg->lastSender = this->UID;
            onErrorMsg(*msg, ErrorType::MY_PING, sender);
          }
          break;

        case MsgType::PONG:

          if (got != this->pingTable.end()) {
            if (got->second != -1) {
              log("received valid msg", *msg);
              msg->lastSender = this->UID;
              onValidPong(*msg, sender);
            } else {
              log("received my PONG!", *msg);
              msg->lastSender = this->UID;
              onErrorMsg(*msg, ErrorType::MY_PONG, sender);
            }
          } else {
            log("error: PONG doesn't found in pingTable", *msg);
            msg->lastSender = this->UID;
            onErrorMsg(*msg, ErrorType::UNOKNOW_PONG, sender);
          }
          break;
        }
      } else {
        log("message discarded!", *msg);
        msg->lastSender = this->UID;
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
  int id = Message::getNextID();

  for (auto& p : this->neighbor) {
    Message *msg = new Message(id, MsgType::PING, this->UID);
    this->pingTable.emplace(id, -1);
    p.second->putMessage(msg);
  }
}

void Peer::log(string s) {
  if (this->logger != nullptr) this->logger->printLog(this->UID, s);
}

void Peer::log(string s, const Message& m) {
  if (this->logger != nullptr) this->logger->printLog(this->UID, s, m);
}
