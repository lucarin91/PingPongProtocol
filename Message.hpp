#ifndef Message_h_
#define Message_h_

#include <iostream>
#include <sstream>

using namespace std;

enum class MsgType { PING, PONG };

class Message {
public:
  int     id;
  MsgType type;
  int     TTL;
  int     HOPS;
  int     originalSender;
  int     lastSender;


  Message(MsgType type,
          int     originalSender);

  Message(int     id,
          MsgType type,
          int     originalSender);

  Message(int     id,
          MsgType type,
          int     originalSender,
          int     lastSender);

  Message(const Message& m);

  string typeToString() const;
  string toString() const;

private:

  static int       MASTER_ID;
  static const int DEFAULT_TTL = 4;
};

// struct MessageWrapper {
//   Message *msg;
//   int      idSender;
//   MessageWrapper(int idSender, Message *msg) : msg(msg), idSender(idSender)
// {}
//
//   // MessageWrapper() {}
// };

#endif // ifndef Message_h_
