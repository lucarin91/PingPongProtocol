#include "TopologyGen.hpp"

using namespace std;
using namespace libconfig;

template<class Peer_Type>
TopologyGen<Peer_Type>::TopologyGen(vector<shared_ptr<Peer> >v) : logger(nullptr),
  peers(v) {}

template<class Peer_Type>
TopologyGen<Peer_Type>::TopologyGen(vector<shared_ptr<Peer> >v,
                                    shared_ptr<Logger>       l) : logger(l),
  peers(v) {}

template<class Peer_Type>
TopologyGen<Peer_Type>::TopologyGen(int N, double c,
                                    long seed) : TopologyGen<Peer_Type>(N,
                                                                        c,
                                                                        seed,
                                                                        nullptr) {}

template<class Peer_Type>
TopologyGen<Peer_Type>::TopologyGen(int               N,
                                    double            c,
                                    long              seed,
                                    shared_ptr<Logger>l) : logger(l) {
  for (int i = 0; i < N; ++i) {
    this->peers.push_back(shared_ptr<Peer_Type>(new Peer_Type()));
  }
  srand(seed);
  generateLink(c);
}

template<class Peer_Type>
TopologyGen<Peer_Type>::TopologyGen(Config& cfg) : logger(nullptr) {
  srand(time(0));
  unsigned n;
  double   c;
  try {
    n = cfg.lookup("peers");
    cout << "peers: " << n << endl;

    c = cfg.lookup("connection");
    cout << "connection: " << c << endl;

    unsigned long seed = cfg.lookup("srand");
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
    cerr << "topology setting not found" << endl;
  }

  for (int i = 0; i < n; i++) {
    auto peerObj = shared_ptr<Peer_Type>(new Peer_Type());
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

  generateLink(c);
}

template<class Peer_Type>
void TopologyGen<Peer_Type>::generateLink(double c) {
  for (int i = 0; i < this->peers.size(); i++) {
    for (int j = 0; j < this->peers.size(); j++) {
      double r = ((double)rand() / (RAND_MAX));

      if (r <= c) this->peers[i]->addNeighbor(this->peers[j]);
    }
  }
}

template<class Peer_Type>
void TopologyGen<Peer_Type>::setLogger(int p, shared_ptr<Logger>l) {
  this->peers[p - 1]->setLogger(l);
}

template<class Peer_Type>
void TopologyGen<Peer_Type>::simulate(function<void(Peer&)>cb) {
  simulate(0, 1, cb);
}

template<class Peer_Type>
void TopologyGen<Peer_Type>::simulate(unsigned int         quanto,
                                      function<void(Peer&)>cb) {
  simulate(0, quanto, cb);
}

template<class Peer_Type>
void TopologyGen<Peer_Type>::simulate(unsigned int         milliseconds,
                                      unsigned int         quanto,
                                      function<void(Peer&)>cb) {
  for (int i = 0; i < this->peers.size(); i++) {
    this->peers[i]->work(quanto);
    cb(*this->peers[i]);

    if (milliseconds != 0) usleep(milliseconds * 1000);
  }
}

template<class Peer_Type>
void TopologyGen<Peer_Type>::print() {
  ostringstream str;

  for (int i = 0; i < this->peers.size(); i++) {
    str << this->peers[i]->getUID() << " -> ";

    for (const auto& p : *this->peers[i]) {
      auto t = p.second.lock();
      str << t->getUID() << " ";
    }
    str << endl;
  }

  if (this->logger) this->logger->printLog(str.str());
}

template<class Peer_Type>
void TopologyGen<Peer_Type>::startPing(int peer) {
  this->peers[peer - 1]->sendPing();
}
