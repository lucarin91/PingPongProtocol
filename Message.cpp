#include "Message.hpp"

int Message::MASTER_ID = 0;

Message::Message(MsgType type, int originalSender) :
  Message(++MASTER_ID, type, originalSender) {}

Message::Message(int id, MsgType type, int originalSender) :
  Message(id, type, originalSender, originalSender) {}

Message::Message(int id, MsgType type, int originalSender, int lastSender) :
  id(id),
  type(type),
  TTL(DEFAULT_TTL),
  HOPS(0),
  originalSender(originalSender),
  lastSender(lastSender) {}

Message::Message(const Message& m) :
  id(m.id),
  type(m.type),
  TTL(m.TTL),
  HOPS(m.HOPS),
  originalSender(m.originalSender),
  lastSender(m.lastSender)  {}

string Message::typeToString() const{
  return this->type == MsgType::PING ? "PING" : (this->type ==
         MsgType::PONG ? "PONG" : "");
}

string Message::toString() const{
  ostringstream stream;
  stream << this->typeToString() << " TTL:" << this->TTL << " hops:" <<
  this->HOPS << " from:" << this->originalSender << " lastSender:" << this->lastSender;
  return stream.str();
}
