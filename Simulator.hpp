#include <iostream>
#include <vector>
#include "Peer.hpp"

class Simulator{
public:
  Simulator();
  ~Simulator();
private:
  std::vector<Peer> peers;
};
