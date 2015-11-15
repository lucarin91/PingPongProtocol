#ifndef Logger_h_
#define Logger_h_

#include <iostream>
#include <sstream>
#include "Message.hpp"

using namespace std;

class Logger {
public:

  Logger(const Logger&) = default;
  Logger& operator=(const Logger&) = delete;
  Logger(Logger&&) = default;
  Logger();
  Logger(string);
  void printLog(int, string) const;
  void printLog(int, string, const Message&) const;

private:
  string fileName;
  bool stdout;
};
#endif // ifndef Logger_h_
