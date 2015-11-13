#ifndef Message_h_
#define Message_h_

#include <iostream>
#include <vector>
#include <unordered_map>

enum class MsgType { PING, PONG };

struct Message {
  int     id;
  MsgType type;
  int     TTL;
  int     HOPS;
  int     sender;
  Message(int id, MsgType type, int TTL, int HOPS, int sender) :
    id(id),
    type(type),
    TTL(TTL),
    HOPS(HOPS),
    sender(sender) {}

  Message(const Message& m) :
    id(m.id),
    type(m.type),
    TTL(m.TTL),
    HOPS(m.HOPS),
    sender(m.sender) {}

    Message(){}
};

// struct MessageWrapper {
//   Message *msg;
//   int      idSender;
//   MessageWrapper(int idSender, Message *msg) : msg(msg), idSender(idSender) {}
//
//   // MessageWrapper() {}
// };

#endif // ifndef Message_h_
