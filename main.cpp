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

using namespace std;
using namespace libconfig;

unsigned sleepTime = 200;
unsigned work      = 2;


int main(int argc, char *argv[]) {
  srand(time(0));
  std::cout << "Ping <--> Pong" << std::endl;

  //
  // Config cfg;
  // try {
  //   cfg.readFile("topology1.cfg");
  // } catch (const FileIOException& fioex) {
  //   std::cerr << "I/O error while reading file." << std::endl;
  //   return 0;
  // } catch (const ParseException& pex) {
  //   std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
  //             << " - " << pex.getError() << std::endl;
  //   return 0;
  // }
  //
  // TopologyGen<Peer_pp> T(cfg);
  //
  // T.print();
  //
  // // T.startPing(8);
  //
  // while (true) {
  //   T.forEach(sleepTime, [&](Peer& p) -> void {
  //     p.work(work);
  //   });
  // }


  shared_ptr<Logger> logger(new Logger());

  Peer_p p1, p2(logger), p3, p4(logger);
  p1.addNeighbor(p2);
  p1.addNeighbor(p3);
  p2.addNeighbor(p4);
  p2.addNeighbor(p3);

  // p2.addNeighbor(p1);

  std::vector<unique_ptr<Peer> > peerVector;
  peerVector.push_back(unique_ptr<Peer>(&p2));
  peerVector.push_back(unique_ptr<Peer>(&p1));
  peerVector.push_back(unique_ptr<Peer>(&p4));
  peerVector.push_back(unique_ptr<Peer>(&p3));

  while (true) {
    for (auto& p : peerVector) {
      (*p).work(1);
      sleep(1);
    }
  }

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
