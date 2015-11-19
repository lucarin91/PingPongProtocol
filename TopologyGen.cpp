#include "TopologyGen.hpp"

using namespace std;
using namespace libconfig;

template<class Peer_Type>
TopologyGen<Peer_Type>::TopologyGen(Config& cfg) : logger(nullptr),
                                                   counterMsg(0) {
    srand(time(0));
  unsigned n;
  double   c;
  try {
    n = cfg.lookup("peers");
    cout << "peers: " << n << endl;

    c = cfg.lookup("connection");
    cout << "connection: " << c << endl;

    int seed = cfg.lookup("srand");
    srand(seed);
    cout << "random seed: " << seed << endl;
  } catch (const SettingNotFoundException& nfex) {
    cerr << "No 'name' setting in configuration file." << endl;
  }
  const Setting& root = cfg.getRoot();

  shared_ptr<Logger> stdLogger(new Logger());
  unordered_map<string, shared_ptr<Logger> > loggerMap;
  bool   stdout;
  string filename;

  try {
    const Setting& loggerPeer = root["logger"]["topology"];

    if (loggerPeer.lookupValue("stdout", stdout) && stdout) {
      this->logger = stdLogger;
    } else if (loggerPeer.lookupValue("filename", filename)) {
      shared_ptr<Logger> newLogger(new Logger(filename));
      loggerMap.emplace(filename, newLogger);
      this->logger = newLogger;
    }
  } catch (const SettingNotFoundException& nfex) {
    cout << "topology setting not found" << endl;
  }
  for (int i = 0; i < n; i++) {
    Peer_Type *peerObj = new Peer_Type();
    this->peers.push_back(peerObj);
    int peerUID = peerObj->getUID();
    try {
      // cout << "logger.p" + to_string(peerUID) << endl;
      const Setting& loggerPeer = root["logger"]["p" + to_string(peerUID)];

      //  if (cfg.lookup("logger.p" + to_string(peerUID))) {


      if (loggerPeer.lookupValue("stdout", stdout) && stdout) {
        peerObj->setLogger(stdLogger);
      } else if (loggerPeer.lookupValue("filename", filename)) {
        auto got = loggerMap.find(filename);

        if (got != loggerMap.end()) peerObj->setLogger(got->second);
        else {
          shared_ptr<Logger> newLogger(new Logger(filename));
          loggerMap.emplace(filename, newLogger);
          peerObj->setLogger(newLogger);
        }
      }
    } catch (const SettingNotFoundException& nfex) {
      //  cerr << "Setting not found" << endl;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      double r = ((double)rand() / (RAND_MAX));

      if (r <= c) this->peers[i]->addNeighbor(*this->peers[j]);
    }
  }
}

template<class Peer_Type>
void TopologyGen<Peer_Type>::setLogger(int p, shared_ptr<Logger>l) {
  this->peers[p - 1]->setLogger(l);
}

template<class Peer_Type>
void TopologyGen<Peer_Type>::forEach(function<void(Peer&)>f) {
  forEach(0, f);
}

template<class Peer_Type>
void TopologyGen<Peer_Type>::forEach(unsigned             milliseconds,
                                     function<void(Peer&)>f) {
  int msgStep = 0;

  for (int i = 0; i < this->peers.size(); i++) {
    f(*this->peers[i]);
    msgStep += this->peers[i].getMsgNumber();
    usleep(milliseconds * 1000);
  }
  counterMsg += msgStep;

  if (this->logger) this->logger->printLog(
      "number of message this step: " + to_string(msgStep) +" total: "+to_string(counterMsg));
}

template<class Peer_Type>
void TopologyGen<Peer_Type>::print() {
  ostringstream str;

  for (int i = 0; i < this->peers.size(); i++) {
    str << this->peers[i]->getUID() << " -> ";

    for (const auto& p : *this->peers[i]) {
      str << p.second->getUID() << " ";
    }
    str << endl;
  }

  if (this->logger) this->logger->printLog(str.str());
}

template<class Peer_Type>
void TopologyGen<Peer_Type>::startPing(int peer) {
  this->peers[peer - 1]->sendPing();
}
