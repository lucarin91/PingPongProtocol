#include <iostream>
#include <vector>
#include <unordered_map>
#include <libconfig.h++>
#include "Peer.hpp"
#include "Peer_p.hpp"
#include "Peer_pp.hpp"
#include "Logger.hpp"
#include "TopologyGen.hpp"
#include "TopologyGen.cpp"
#include "ArgsParser.hpp"

using namespace std;
using namespace libconfig;

unsigned sleepTime = 1000;
unsigned work      = 2;


int main(int argc, char *argv[]) {
  std::cout << "Ping <--> Pong" << std::endl;

  Config cfg;

  shared_ptr<Logger> logger(new Logger());
  char *cfgName = ArgsParser::getArgument(argc, argv, "-c");

  if (cfgName) {
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
  #if V1
    TopologyGen<Peer> T(cfg);
  #endif // if V1
  #if V2
    TopologyGen<Peer_p> T(cfg);
  #endif // if V2
  #if V3
    TopologyGen<Peer_pp> T(cfg);
  #endif // if V3

    T.print();

    // T.startPing(1);
    int nMsg = 0;

    for (int i = 0; i < 100000; i++) {
      int stepMsg = 0;
      T.simulate(sleepTime, work, [&](Peer& p) -> void {
        stepMsg += p.getLastStatistics();
      });

      if (stepMsg != 0) {
        nMsg += stepMsg;
        logger->printLog(">>>>>>>>>>>>>> STEP_MSG: " + to_string(
                           stepMsg) + " - TOT_MSG: " + to_string(
                           nMsg) + " <<<<<<<<<<<<<<<<<\n\n");
      }
    }
  }


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

  return 0;
}
