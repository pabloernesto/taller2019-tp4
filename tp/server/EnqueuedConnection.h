#ifndef ENQUEUEDCONN_H_
#define ENQUEUEDCONN_H_

#include "../common/socket.h"
#include "../common/blockingqueue.h"
#include <string>
#include <thread>

// This file describes the public interface of the Enqueued Connection (EQ)
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
  BlockingQueue<std::string> q;

  Receiver(Connection& c);
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
  // The client class may be seen as a queue, sending and receiving data.
  // This class may later be modified to supply a queue-like interface.
  void Push(std::string&& s);
  bool IsPopable();
  std::string Pop();

  // Shutdown the underlying network connection and close the outgoing queue.
  // The EQ will try to send the rest of the outgoing messages before
  // before it destroys itself.
  void Shutdown();

  EnqueuedConnection(Connection&& c);
  ~EnqueuedConnection();
};

#endif  // ENQUEUEDCONN_H_
