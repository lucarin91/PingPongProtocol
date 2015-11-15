#ifndef Logger_h_
#define Logger_h_

#include <iostream>
#include <fstream>
#include <sstream>
#include "Message.hpp"

using namespace std;

class Logger {
public:

  Logger(const Logger&) = default;
  Logger& operator=(const Logger&) = delete;
  Logger(Logger&&) = default;
  Logger();
  ~Logger();
  Logger(string);
  void printLog(string);
  void printLog(int, string);
  void printLog(int, string, const Message&);

private:
  ofstream file;
  bool stdout;
};
#endif // ifndef Logger_h_
