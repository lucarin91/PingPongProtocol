#include <iostream>
#include <vector>
#include <unistd.h>
#include "Peer.hpp"
#include "Peer_p.hpp"
#include "Logger.hpp"
#include "TopologyGen.hpp"

using namespace std;

int main (int argc, char* argv[]){
  srand(time(0));
  std::cout << "Ping <--> Pong" << std::endl;
  shared_ptr<Logger> logger(new Logger());

//   Peer_p p1,p2(logger),p3,p4(logger);
//   p1.addNeighbor(p2);
//   p1.addNeighbor(p3);
//   p2.addNeighbor(p4);
//   p2.addNeighbor(p3);
//   // p2.addNeighbor(p1);
//
// //  p2.sendPing();
//
//   std::vector<unique_ptr<Peer>> peerVector;
//   peerVector.push_back(unique_ptr<Peer>(&p2));
//   peerVector.push_back(unique_ptr<Peer>(&p1));
//   peerVector.push_back(unique_ptr<Peer>(&p4));
//   peerVector.push_back(unique_ptr<Peer>(&p3));

  TopologyGen T (10,0.2);

  T.setLogger(2,logger);
  T.setLogger(5,logger);
  T.print();

  while (true){
    T.forEach([&](Peer& p )->void{
      p.work(2);
      sleep(1);
    });
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
