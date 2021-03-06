#ifndef Message_h_
#define Message_h_

#include <iostream>
#include <sstream>

using namespace std;

enum class MsgType { PING, PONG };

class Message {
  static unsigned long MASTER_ID;
  static const int DEFAULT_TTL = 4;

public:

  unsigned long id;
  MsgType type;
  int     TTL;
  int     HOPS;
  int     originalSender;
  int     lastSender;


  Message(MsgType type,
          int     originalSender);

  Message(unsigned long id,
          MsgType type,
          int     originalSender);

  Message(unsigned long     id,
          MsgType type,
          int     originalSender,
          int     lastSender);

  Message(const Message& m);

  string           typeToString() const;
  string           toString() const;
  static const int getNextID() {
    return ++MASTER_ID;
  }
};
#endif // ifndef Message_h_
