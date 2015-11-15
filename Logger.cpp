#include "Logger.hpp"

using namespace std;

Logger::Logger() : stdout(true) {}

Logger::Logger(string filename) {
  this->stdout = false;
  this->file.open (filename);
  this->file << "PING <-logfile-> PONG" << endl;
}

Logger::~Logger(){
  this->file.close();
}

void Logger::printLog(int peer, string s){
  ostringstream str;
  str << "peer " << peer << " >> " << s;
  printLog(str.str());
}

void Logger::printLog(string s){
  if (this->stdout) {
    cout << s << endl;
  }else{
    this->file << s << endl;
  }
}

void Logger::printLog(int peer, string s, const Message& m) {
  printLog(peer, s + " " + m.toString());
}
