#include <iostream>
#include <vector>
#include <unordered_map>
#include <libconfig.h++>
#include "Peer/Peer.hpp"
#include "Peer/Peer_p.hpp"
#include "Peer/Peer_pp.hpp"
#include "Helper/Logger.hpp"
#include "TopologyGen.hpp"
#include "TopologyGen.cpp"
#include "Helper/ArgsParser.hpp"

using namespace std;
using namespace libconfig;

unsigned sleepTime = 500;
unsigned work      = 1;

unsigned short synbol = 0;


int main(int argc, char *argv[]) {
  char  *cfgName    = ArgsParser::getArgument(argc, argv, "-c");
  char  *Nchar      = ArgsParser::getArgument(argc, argv, "-n");
  int    N          = Nchar ? atoi(Nchar) : 0;
  char  *conChar    = ArgsParser::getArgument(argc, argv, "-p");
  double connection = conChar ? stod(conChar) : 0;
  char  *stepChar   = ArgsParser::getArgument(argc, argv, "-s");
  int    step       = stepChar ? atoi(stepChar) : 0;
  bool print = ArgsParser::existArgument(argc,argv,"--print");
  shared_ptr<Logger> logger(new Logger());

#if V1
  TopologyGen<Peer> *T;
#endif // if V1
#if V2
  TopologyGen<Peer_p> *T;
#endif // if V2
#if V3
  TopologyGen<Peer_pp> *T;
#endif // if V3

  if (cfgName) {
    std::cout << "Ping <--> Pong" << std::endl;
    Config cfg;
    try {
      cfg.readFile(cfgName);
    } catch (const FileIOException& fioex) {
      std::cerr << "I/O error while reading file." << std::endl;
      return 0;
    } catch (const ParseException& pex) {
      std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                << " - " << pex.getError() << std::endl;
      return 0;
    }
#if V1
    T = new TopologyGen<Peer>(cfg);
    T->startPing(1);
#endif // if V1
#if V2
    T = new TopologyGen<Peer_p>(cfg);
#endif // if V2
#if V3
    T = new TopologyGen<Peer_pp>(cfg);
#endif // if V3

    T->print();
  } else if  (N && connection) {
    char  *seedChar   = ArgsParser::getArgument(argc, argv, "-r");
    long   seed       = seedChar ? stol(seedChar) : time(0);
    shared_ptr<Logger> tLogger(new Logger("topology_test.log"));
#if V1
    T = new TopologyGen<Peer>(N, connection, seed, tLogger);
    T->startPing(1);
#endif // if V1
#if V2
    T = new TopologyGen<Peer_p>(N, connection, seed, tLogger);
#endif // if V2
#if V3
    T = new TopologyGen<Peer_pp>(N, connection, seed, tLogger);
#endif // if V3
    sleepTime = 0;
    logger    = nullptr;
    //step      = 1000;
  } else {
    std::cout <<
    "-c <conf> \t the name of the configuration file, if given only the step number are consider"
              << std::endl;
    std::cout << "-n <number> \t number of peers" << std::endl;
    std::cout << "-p <number> \t probability of connection from 0 to 1" <<
    std::endl;
    std::cout << "-r <number> \t random seed" << std::endl;
    std::cout << "-s <number> \t number of step" << std::endl;
    return 0;
  }
  int nMsg = 0;

  for (int i = 0; i < step || step == 0; i++) {
    int stepMsg = 0;
    T->simulate(sleepTime, work, [&](Peer& p) -> void {
      stepMsg += p.getLastStatistics();
    });

    if (stepMsg != 0) {
      nMsg += stepMsg;

      if (logger) logger->printLog(">>>>>>>>>>>>>> STEP_MSG: " + to_string(
                                     stepMsg) + " - TOT_MSG: " + to_string(
                                     nMsg) + " <<<<<<<<<<<<<<<<<\n\n");
    }
    //|/-\ |/-\

    if (print){
      cout << "\r" << (75<++synbol%100?"\\":
                       50<synbol%100?"-":
                       25<synbol%100?"/":
                       "|") << " Total Number of MSG: " << nMsg <<flush;

                       //usleep(10000);
                       //synbol++;
                     }
  }
  if (print) cout<<endl;
  cout << nMsg << endl;
  delete T;
  return 0;
}

// }else{
//   Peer p1, p2(logger), p3, p4;
//   p1.addNeighbor(shared_ptr<Peer>(&p2));
//   p1.addNeighbor(shared_ptr<Peer>(&p3));
//   p2.addNeighbor(shared_ptr<Peer>(&p4));
//   p2.addNeighbor(shared_ptr<Peer>(&p3));
//   //p2.sendPing();
//
//   std::vector<shared_ptr<Peer> > peerVector;
//   peerVector.push_back(shared_ptr<Peer>(&p2));
//   peerVector.push_back(shared_ptr<Peer>(&p1));
//   peerVector.push_back(shared_ptr<Peer>(&p4));
//   peerVector.push_back(shared_ptr<Peer>(&p3));
//
//   TopologyGen<Peer_pp> T (move(peerVector),logger));
// }
//
// for (int i =0;i<1000;i++) {
//   for (auto& p : peerVector) {
//     p->work(1);
//     sleep(1);
//   }
// }

// std::vector<Peer*> peerVector;
// peerVector.push_back(&p1);
// peerVector.push_back(&p2);
// peerVector.push_back(&p3);
// peerVector.push_back(&p4);
//
// while (true){
//   for (Peer* p : peerVector){
//     p->doWork(1);
//     sleep(1);
//   }
// }
