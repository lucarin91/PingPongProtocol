#include "TopologyGen.hpp"

using namespace std;

TopologyGen::TopologyGen(int n, double c){
  srand(time(0));
  for (int i = 0; i<n; i++){
    this->peers.push_back(new Peer_p());
  }
  for (int i = 0; i<n; i++){
    for (int j=0; j<n; j++){
      double r = ((double) rand() / (RAND_MAX));
      cout<<r<<endl;
      if ( r <= c )
        this->peers[i]->addNeighbor(*this->peers[j]);
    }
  }
}

void TopologyGen::setLogger(int p, shared_ptr<Logger> l){
  this->peers[p-1]->setLogger(l);
}

void TopologyGen::forEach(function<void(Peer&)> f){
    for (int i=0; i<this->peers.size(); i++){
      f(*this->peers[i]);
    }
}

void TopologyGen::print(){
  for (int i=0; i<this->peers.size(); i++){
    cout << this->peers[i]->getUID() << " -> ";
    for (auto& p : this->peers[i]->neighbor) {
      cout << p.first << " ";
    }
    cout << endl;
  }
}
