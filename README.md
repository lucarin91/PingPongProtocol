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
The principle structure is composed by three class `TopologyGen`, `Peer` and `Message`.


# Statistics


# How run it
