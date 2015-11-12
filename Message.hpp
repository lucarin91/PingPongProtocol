#ifndef Message_h_
#define Message_h_

#include <iostream>
#include <vector>
#include <unordered_map>
#include "Peer.hpp"

enum class MsgType { PING, PONG };

struct Message {
  int     id;
  MsgType type;
  int     TTL;
  int     HOPS;
  Message(int id, MsgType type, int TTL, int HOPS) :
    id(id),
    type(type),
    TTL(TTL),
    HOPS(HOPS) {}
};

struct MessageWrapper {
  Message msg;
  Peer    sender;
  MessageWrapper(Message msg, Peer sender) : msg(msg), sender(sender) {}
};

#endif // ifndef Message_h_
