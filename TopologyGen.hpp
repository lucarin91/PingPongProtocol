#ifndef TopologyGen_h_
#define TopologyGen_h_

#include <vector>
#include <iostream>
#include <memory>
#include <cmath>
#include <unistd.h>
#include <libconfig.h++>
#include "Peer.hpp"
#include "Peer_p.hpp"
#include "Logger.hpp"

using namespace std;
using namespace libconfig;

template<class Peer_Type>class TopologyGen {
  shared_ptr<Logger> logger;
  vector<shared_ptr<Peer>> peers;
public:

  TopologyGen(const TopologyGen&)            = delete;
  TopologyGen& operator=(const TopologyGen&) = delete;
  TopologyGen(TopologyGen &&)                = delete;

  TopologyGen(vector<shared_ptr<Peer>>);
  TopologyGen(vector<shared_ptr<Peer>>, shared_ptr<Logger>);
  TopologyGen(Config&);

  void setLogger(int,
                 shared_ptr<Logger>);
  void startPing(int p);
  void forEach(function<void(Peer&)>);
  void forEach(unsigned,
               function<void(Peer&)>);
  void print();
};
#endif // ifndef TopologyGen_h_
