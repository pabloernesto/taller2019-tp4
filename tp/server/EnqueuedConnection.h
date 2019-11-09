#ifndef ENQUEUEDCONN_H_
#define ENQUEUEDCONN_H_

#include "../common/socket.h"
#include "../common/blockingqueue.h"
#include <string>
#include <thread>

// This file describes the public interface of the Enqueued Connection (EC)
// class. This class provides continuous reading/writing over a network
// connection, and sinchronization of the shared resource.

// Note: Since both Sender and Receiver are implementation details
// for EC, and not really meant as part of the module's public interface,
// I've used public attributes liberally.

// A Sender continuosly reads from a queue of outgoing data, and writes it
// to the network connection.
class Sender {
  Connection& connection;
  std::thread t;
  void Loop();

public:
  BlockingQueue<std::string> q;

  Sender(Connection& c);
  void Start();
  void Join();
};

// A Receiver continuously reads from a network connection, and pushes incoming
// data to a queue.
class Receiver {
  Connection& connection;
  std::thread t;
  void Loop();

public:
  BlockingQueue<std::string>* q;

  Receiver(Connection& c, BlockingQueue<std::string>* in_queue);
  void Start();
  void Join();
};

// Both these classes are tied together by virtue of sharing a network
// connection.
class EnqueuedConnection {
  Connection connection;

  // However, their operative details are irrelevant to data producers and
  // consumers, so they remain private members of the Client class.
  Sender sender;
  Receiver receiver;

public:
  BlockingQueue<std::string>& GetOutgoingQueue();
  BlockingQueue<std::string>& GetIncomingQueue();

  // Rebind EC's Receiver to place incoming messages on the supplied queue.
  void SetIncomingQueue(BlockingQueue<std::string>& q);

  // Shutdown the underlying network connection and close the outgoing queue.
  // The EC will try to send the rest of the outgoing messages before
  // before it destroys itself.
  void Shutdown();

  EnqueuedConnection(Connection&& c, BlockingQueue<std::string>& in_queue);
  ~EnqueuedConnection();
};

#endif  // ENQUEUEDCONN_H_
