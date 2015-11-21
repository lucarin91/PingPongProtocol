# Ping/Pong protocol simulation
The scope of this project is to simulate the PING/PONG protocol in a GNutella network. The software hime to simulate this kind of protocol, and all the test are done in with this purpuse, but actually the general contruction can bring this software to future extension for other p2p simulation.

The idea of the software is to create an infinite loop where each time the simulation engine call a peer to execute same of its tasks, that in this specific case are pop a message from the buffer and work with it. To better simulate the this specific protocol the Peer have also, as in the real work, the possibility to wait same amount of time, and then do something.

# Feature
- Random peer topology generation, given the number of nodes, the probability of connection and a random seed.
- Prob and log a set of specific peers, either in the standard output or in a file.
- Simple json like configuration file.
- Two different mode: simulation with the log of the behaver of the peer and  simple message analyses.
- Three type of implementation of the PING/PONG protocol, on demand, with persistent cache and dynamic cache.
- Simple Peer interface easily extendibles with the onEvent methods.

# Implementation
The principle structure of the project is composed by the class `TopologyGen`, to manage and generate the peer structure, `Peer` rappresent a peer entity with or the logic to mplement the protocal, and `Message` that simulate the structure of the ping ping message with the needed information.

The to implement the three different type of the protocal the calss Peer is extended and create the other two class `Peer_p` and `Peer_pp`.

### TopologyGen
This class enerate and manage a peer topology, it can random create a peer connection or mannualy give a already define vector of peers. Here are the main contructor:
- `TopologyGen(vector<shared_ptr<Peer>> peers_list)` create a topologyGen object given an already define vector of Peers.

- `TopologyGen(Config& configuration_file)`  create a topologyGen object given a configuration file, it use the parameters in the configuration file to create a random topology.

- `TopologyGen(int n_of_node, double connection, long r_seed)`  create a topologyGen object manually given the number of nodes, the probability of connection and a random seed.


After the creation of the object is possible to interact with the peer by the following method:

- `void simulate(function<void(Peer&)> call_back)` this is the main interface with the peers, The function execute one cycle of simulation among the peers, and after execute the callback function. There are other version of this function in witch is possible to specified, how much work each peer have to compute, and the sleep time among different peer iteration.

- `void startPing(int p)` manually trigger the send of the ping message of one specific peer, it is usesful in the first version of the simutation, when the peer *on demand* send the pings.

- `void print()` this function just print the topology structure of the peers.



### Peer
It is the class specifying all the characteristic of a peer in the network, it have a list of connected peers, and a message queue where the other peers can put messages.
A. It can be created by the following constructor:
- `Peer()` create a new Peer with a unique id.
- `Peer(int uid, shared_ptr<Logger> l)` create a new instance with a specific id and a Logger object
- `Peer(shared_ptr<Logger> l)` create a new instance with a Logger.

- `void work(int time_quanto)` this method run th enumber of time rappresentat of the parameter time_quanto same work of the peers, this rappresent the real execution of the peer work. When invoked basically the peer first check if same timer are elapsed, and then pop a number of message equal to the parameter `time_quanto` from the queue, and then work on it.  

- `void putMessage(unique_ptr<Message> msg)` put a new message in the queue of the peer.

- `void sendPing()` trigger the peer to broadcast a new ping message to all their neighbor.

- `bool addNeighbor(shared_ptr<Peer> p)` add a new neighbor to the peer, this method simulate a bidirectional connection to a new peer. In this way after the executing of the method the two peers will have in their neighbor list the new connection.


In the Peer class there is also other event based method used to implement the actual behavior when a PING or PONG message arrive. This method are actually the method extended by the `Peer_p` ans `Peer_pp` class. More in detail we can see:
- `virtual void onValidPing(unique_ptr<Message> msg , int sender_neighbor)` and `virtual void onValidPong(unique_ptr<Message> msg, int sender_neighbor)` called when the peer receives a valid ping or pong (the TTL is not 0) with the received message and the neighbor that send it.

- `virtual void onErrorMsg(unique_ptr<Message> msg, ErrorType error, int neighbor)` called when a not valid message is sent to the peer, it contains a `ErrorType` that rapprendet the specific error of the message. It can be one of the following:
- `ALREADY_FORWARDED_PING` received a ping that is already forwarded and already is in my ping table.
- `UNOKNOW_PONG` received a pong for witch there isn't information in the ping table, so the routing back information is missong.
- `EXPIRED_MSG` the message received have a experied TTL.
- `MY_PING` receive my ping
- `MY_PONG` receive my pong, so actually it is good, it is here only to have a more general structure of the system.

### Message


# Statistics


# How run it
