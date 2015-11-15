#ifndef TopologyGen_h_
#define TopologyGen_h_

#include <vector>
#include <iostream>
#include <memory>
#include <cmath>
#include <time.h>
#include "Peer.hpp"
#include "Peer_p.hpp"
#include "Logger.hpp"

using namespace std;

class TopologyGen {
public:

  TopologyGen(const TopologyGen&)            = delete;
  TopologyGen& operator=(const TopologyGen&) = delete;
  TopologyGen(TopologyGen&&)                 = delete;

  TopologyGen(int, double);
  TopologyGen(vector<Peer>, double);

  void setLogger(int, shared_ptr<Logger>);
  void forEach(function<void(Peer&)>);
  void print();

private:

  vector<Peer*> peers;

};
#endif // ifndef TopologyGen_h_
