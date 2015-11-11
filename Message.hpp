#ifndef Message_h_
#define Message_h_

#include <iostream>
#include <vector>
#include <unordered_map>

enum class MsgType { PING, PONG };

struct Message{
  int id;
  MsgType type;
  int TTL;
  int HOPS;
  Message(int id, MsgType type, int TTL, int HOPS) :
    id(id),
    type(type),
    TTL(TTL),
    HOPS(HOPS) {}
};

#endif
