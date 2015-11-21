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
  vector<shared_ptr<Peer> > peers;
  void generateLink(double);

public:

  TopologyGen(const TopologyGen&)            = delete;
  TopologyGen& operator=(const TopologyGen&) = delete;
  TopologyGen(TopologyGen&&)                 = delete;

  TopologyGen(vector<shared_ptr<Peer> >);
  TopologyGen(vector<shared_ptr<Peer> >,
              shared_ptr<Logger>);
  TopologyGen(Config&);
  TopologyGen(int,
              double,
              long);
  TopologyGen(int,
              double,
              long,
              shared_ptr<Logger>);

  void setLogger(int,
                 shared_ptr<Logger>);
  void startPing(int p);
  void simulate(function<void(Peer&)>);
  void simulate(unsigned int,
                function<void(Peer&)>);
  void simulate(unsigned int,
                unsigned int,
                function<void(Peer&)>);
  void print();
};
#endif // ifndef TopologyGen_h_
