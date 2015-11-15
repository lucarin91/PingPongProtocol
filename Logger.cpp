#include "Logger.hpp"

using namespace std;

Logger::Logger() : stdout(true) {}

Logger::Logger(string filename) : fileName(filename), stdout(false) {}

void Logger::printLog(int peer, string s) const{
  if (this->stdout) {
    cout << "peer " << peer << " >> " << s << endl;
  }
}

void Logger::printLog(int peer, string s, const Message& m) const {
  printLog(peer, s + " " + m.toString());
}
