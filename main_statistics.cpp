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

unsigned sleepTime = 0;
unsigned work      = 1;


int main(int argc, char *argv[]) {
  srand(time(0));

  // td::cout << "Ping <--> Pong" << std::endl;

  shared_ptr<Logger> logger(new Logger("topology_test.log"));
  int N = atoi(ArgsParser::getArgument(argc, argv, "-n"));
  double connection = stod(ArgsParser::getArgument(argc, argv, "-c"));
  long   seed       = stol(ArgsParser::getArgument(argc, argv, "-r"));
  int    step       = atoi(ArgsParser::getArgument(argc, argv, "-s"));

  if (N && step && connection && seed) {
    #if V1
    TopologyGen<Peer> T(N, connection, seed, logger);
    #endif // if V1
    #if V2
    TopologyGen<Peer_p> T(N, connection, seed, logger);
    #endif // if V2
    #if V3
    TopologyGen<Peer_pp> T(N, connection, seed, logger);
    #endif // if V3

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
    //   T = move(new TopologyGen<Peer_pp>(move(peerVector),logger));
    // }

    T.print();

    // T.startPing(1);
    unsigned long nMsg = 0;

    #if 0
    time_t end = time(0)+60*2;
    while(time(0)<end) {
    #endif
    #if 1
    for (int i = 0; i < step; i++) {
    #endif
      unsigned long stepMsg = 0;
      T.simulate(work, [&](Peer& p) -> void {
        stepMsg += p.getLastStatistics();
      });

      if (stepMsg != 0) {
        nMsg += stepMsg;

        // cout << "\rTOT_MSG: " << nMsg;
      }
    }
    cout << nMsg << endl;

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
  }
  return 0;
}
