# Ping/Pong protocol simulation
The scope of this project is to simulate the Ping/Pong protocol in a Gnutella network. The software aim to simulate this kind of protocol, and all the test are done in with this purpose, but actually the general structure of the project can lead to future extension and simulation of other p2p protocal.

![Simulator in action](img/example-small.jpg)

Briefly the software have an *infinite* loop where each time the simulation engine call a peer to execute same tasks, usually pop a message out of the message queue and work with it. To better simulate the this specific protocol the peer have also the possibility to set a time out, and execute something task, as send a ping, after that.

# Feature
- Random peer topology generation, given the number of nodes and the probability of connection.
- Probe and log a set of specific peers, either in the standard output or in one and more file.
- Simple json like configuration file.
- Two different mode: simulation with the log of the behaver of the peer and simple message analyses.
- Three type of implementation of the Ping/Pong protocol, on demand, with simple cache and dynamic cache.
- Simple Peer interface easily extendibles with the onEvent methods.


# How To Use it
## Requirement:
- Linux system
- g++ >= 4.8 with c++11 support
- cMake >= 3.0
- libconfig++, on ubuntu/debian system just `sudo apt-get update && sudo apt-get install libconfig++8-dev -y`

## Download and Install
Download the last version of the software with git command or by downloading the zip file:
```
cd ~
git clone ...
```
Go inside the created directory and create the build folder where compile the program:
```
mkdir build && cd build
```
create the makefile with cmake and start the compilation:
```
cmake ..
make
```
Now the simulator is correctly compiled and you can find the three version of the simulation in different executable in the `/bin` folder inside the `PingPongProtocal` directory:
- `PingPongProtocal_v1` the first version without cache.
- `PingPongProtocal_v2` the second version with simple cache.
- `PingPongProtocal_v3` the third version with the dynamic cache.

## How To Run it
To run one of the three simulation you have to create a configuration file or use one of the given example. For instance you can ru the silumation of the second version of the protocol with the configuration file `topology_2.cfg`, with the following:
```
bin/PingPongProtocal_v2 -c example/topology_2.cfg
```
That configuration file create a random topology with 50 peers, 0.1 as connections probability and a random seed of 234234324443334. Instead in the *logger* property is specified witch peer have to be logged and where, in the specific example: only the peer 23, 10, 3 and 15 have to be logged, and respectelly on the standard output for the first two and the file  `pippo.log` for the second 2. It's also specified that the random graph topology of the peer have to be write to the `topology.log` file.

Are different option on the executable, the `-c` say that a configuration file is given, but can pass also the number of step of the simulation loop with the parameter `-s`.

To just use the simulator only for print the number of message in the network and without any other additional information, for example to run same statistics, you can use instead the parameters:
- `-n` number of node in the network
- `-p` probability of connections
- `-r` the random seed

If you use at least one of them all the printing information are disabled. A possible command in this sense can be:
```
bin/PingPongProtocal_v2 -n 1000 -p 0.1 -s 1000 -r 4815162342   
```

# Key point in the Ping/Pong implementation
In this section we will see all the key idea behind the implementation of the three version of the Ping/Pong protocol. In general we can say that all the simulation is about the row communication of the peer and how the message are distributed in the network; for this reason there isn't any kind of simulation of the socket connection or error in the network communication.

## On demand ping
This is the base structure of the ping/pong protocol, the peer are externally triggered and broadcasts a ping to all its neighbors, this is done by using the method `putMessage(Message)` which push a new message on the other peer's queue. Then all the peer that receive a Ping respond with a Pong and forward the ping to the other connected peer.

An important aspect is how the Pong message are routing toward the original sender of the ping. To achieve this is used an HashMap in which store the original sender of every received Ping message. This structure have as key the id of the message and as value the UID of the neighbor that send that message (in general it can be different from the original sender). In this way exploiting this information the peers can hoop by hoop back routing the Pong to the original sender. More in detail this is the used structure:

```
std::unordered_map<int, int> pingTable;
```

It's important to consider that the access of this structure is in constant time, so this create the minimal overhead every time the peer receive one Pong. The same structure is also used to recognize the Ping sent by the peer itself or the its answer Pong, in fact each time a peer send a new ping it insert in the pingTable the id of the message and a constant -1.
In this way is possible to do same other check during the ping forwarding, to improve the effective of the broadcast and reduce the content replication:
- not forwarded the ping already forwarded, is possible that there is a cycle in the peer graph.
- recognize and don't forward its Ping.
- recognize and don't forward its Pong.

## Simple Pong Cache
This version of the peer have all the structure explained before for the on demand ping, but it also include:
- the ping are sent after a variable number of second (by default random between 5 and 30 seconds)
- the peer exploit a cache of Pong, that avoid to forward every time all the Ping to the neighbor.

The implementation of the pongCache is driven by the idea to have a fasten data structure with constant time for insertion and retrieval, because it have to be access every time a peer receive a new ping from the network.

Practically the structure is a HashMap of HashMap, to exploit the constant access to retrieve the cache entry for one of the neighbor, and to avoid replication of the Pong of the same original sender.
```
std::unordered_map<int, // neighbor id
                   std::unordered_map<int, // original sender
                                      unique_ptr<Message>>> pongCache;
```
So logically the structure it can be consider a set of different caches, one for every neighbor, in which inside there are a key value pair, with the original sender of the message and the message it self.

To clarify this type of structure we can analyses the behavior of the cache when it will be filled by new Pong and when this Pong are retrieved and send back to the requester.

First of all every time a new Pong arrive from one of the incoming link this new message is saved in the cache of that neighbor using the UID of the original sender as second index of the structure. In this way every time a new Pong from the same original sender arrive it override the old one and not create any duplication in the cache.

In the other case study when a new Ping arrive from one of the neighbor ping, it starts a loop on all the cache of the neighbor and if at least one message is present on that cache, it will be send to the requester and the ping is not forwarding on that link.

# Dynamic Pong Cache
This version of the peer have all the cache facility of the previous version, but improve the system with a dynamic cache where every entry are deleted after a number of second (by default 60). To create this new feature the previous cache structure is kept untouched and instead is added a Linked List where put all the time information needed by filtering process.

More in detail every time the peer receive a Pong it store the it in the pongCache as in the previous example, but now it also add a new entry in the timeList at the end of the list, with the the timestap generated by adding the actual time to the default experience value of 60 seconds. In this way the list is every time ordered by the time stamp of the cache entry.

Than every 30 second by default the filtering process of the cache start, and the list is scanned to find element with a time stamp less of the actual time. When a entry with this characteristic is found the system use the information stored inside the linked list node to remove the cache entry in the pongCache, and also the entry in the timeList is popped out. It can be easily see that the process filtering process can be stop before that all the list is scanned, it is because when a list node with a greater time stamp of the actual time is found, no other node with less time stamp can be found in the list.

# Implementation Detail
In this section we will see more in detail the structure of the classes with a description of the more relevant constructor and method for each of them.
The main class in the project are the `TopologyGen`, that manage and generate the peer structure, the `Peer` that represent a peer entity and the `Message` that simulate the structure of the Ping/Pong message with the needed information.
Than there are same utility class as the `ArgsParser` to read the argument of the command line and the `Logger` used to probe and log the activity of a set of peers.

## TopologyGen
This class generates and manages the peer topology, it can random create a peer topology given a configuration file or it possible to manually give an already define vector of peers. Here are the main constructor:
- `TopologyGen(vector<shared_ptr<Peer>> peers_list)` create a TopologyGen object given an already define vector of Peers.

- `TopologyGen(Config& configuration_file)`  create a TopologyGen object given a configuration file, it use the parameters in the configuration file to create a random topology.

- `TopologyGen(int n_of_node, double connection, long r_seed)`  create a topologyGen object manually given the number of nodes, the probability of connection and a random seed.


After the creation of the object is possible to interact with the peer by the following method:

- `void simulate(function<void(Peer&)> call_back)` this is the main interface with the peers, this function execute one cycle of simulation among the peers, and after execute the callback function. There are other version of this function in witch is possible to specified, how much work each peer have to compute, and the sleep time between to peer execution.

- `void startPing(int p)` manually trigger a given peer to send a ping message to all its neighbor, it is used in the *on demand* version of the Ping/Pong.

- `void print()` this function just print the topology structure of the peers.

## Peer
It is the class specifying all the characteristic of a peer in the network, it have a list of connected peers, and a message queue where the other peers can put messages. It can be created by the following constructor:
- `Peer()` create a new Peer with a unique id.
- `Peer(int uid, shared_ptr<Logger> l)` create a new instance with a specific id and a Logger object
- `Peer(shared_ptr<Logger> l)` create a new instance with a Logger.

- `void work(int time_quanto)` this method run for a number of time set by the parameter `time_quanto` the work of the peer. When invoked basically the peer first check if one of is timer are elapsed and then pop a number of message equal to the parameter `time_quanto` from the queue, and then work on it.  

- `void putMessage(unique_ptr<Message> msg)` put a new message in the queue of the peer.

- `void sendPing()` trigger the peer to broadcast a new ping message to all their neighbor.

- `bool addNeighbor(shared_ptr<Peer> p)` add a new neighbor to the peer, this method simulate a bidirectional connection to a new peer. In this way after the executing of the method the two peers will have in their neighbor list the new connection.

In the Peer class there is also other event based method used to implement the actual behavior of the Ping/Pong message protocal. This method are actually the one extended by the `Peer_p` an `Peer_pp` class. More in detail we can see:
- `virtual void onValidPing(unique_ptr<Message> msg , int sender_neighbor)` and `virtual void onValidPong(unique_ptr<Message> msg, int sender_neighbor)` called when the peer receives a valid Ping or Pong (the TTL is not 0) with the received message and the neighbor that send it.
- `virtual void onErrorMsg(unique_ptr<Message> msg, ErrorType error, int neighbor)` called when a not valid message is sent to the peer, it contains a `ErrorType` that represent the specific error of the message. It can be one of the following:
- `ALREADY_FORWARDED_PING` received a ping that is already forwarded and already is in my ping table.
- `UNOKNOW_PONG` received a Pong for witch there isn't information in the ping table, so the routing back information is missing.
- `EXPIRED_MSG` the message received have a expired TTL.
- `MY_PING` receive my Ping
- `MY_PONG` receive my Pong, so actually it is good, it is here only to have a more general structure of the system.

## Message
This class represent the actual message exchanged between the peers. It don't have the exact structure of the PING/PONG message, but keep all the information needed to simulate the same behavior. The actual field are:
- `int id` the unique id of the message.
- `MsgType type` the type of the message: `PING` or `PONG`
- `int TTL` the time to live of the message by default it is set to 4
- `int HOPS` the hops that the message did, how many peer it traverse
- `int originalSender` it represent the id of the peer that generate the message the first time.
- `int lastSender` it represent the previous hop sender, in other words the neighbor that send the message to the peer. In a real protocol implementation this information can be taken by the socket connection information, but this simulation each entry in the queue are identically so it is important to distinguish witch neighbor put that message.

## Peer_p
This class extended `Peer` and add the a Pong cache with the possibility to exploit the already saved Pong instead of broadcast every time the Ping and wait for all the Pong. This is implemented by the following method called when a valid Ping or Pong are received:

- `virtual bool addPongCache(int neighbor, unique_ptr<Message> msg)` this store a message in the pongCache using the neighbor_id as key of the HashMap, to achieve constant time retrieve.

- `virtual void sendChachedPong(int to,unique_ptr<Message> msg)` if at least one message is in the pong cache, send this pong without broadcast the ping. If no message are found in the cache the ping is regularly broadcast to the neighbor.

## Peer_pp
This class extended the `Peer_p` and add a linked list in witch store the time stamp of every cache entry. The node store inside the list have the following field:
```
struct ListNode {
  time_t tstamp;         //time stamp of the entry
  int    original_sender;
  int    neighbor_id;
  int    msg_id;
};
```
Extending the on `addPongCache` method of the `Peer_p` class each time a new pong is added to the cache is also add at the end of the list a new entry of the ListNode struct. The list in this way is organize with ordered time stamp.
Then to add the capability to send the Pong store in the cache only if they are more that K, also the method `sendChachedPong` of the class `Peer_p` was extended.

This class add also another timeout that by default every 60 second by default check and clear the cache entry, as it is describe in the previous section.

# Statistics
One of the aim of this project is to run same analysis on the Ping/Pong protocol, and verify is the proposed cache implementation, work in practice, and if the system can scale in a large system. It's decide to confront only the two version of the cache implementation, because the first version doesn't have any periodically ping system and so can be directly confronted two the other.
