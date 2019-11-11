#include "EnqueuedConnection.h"

static const int QUEUE_SIZE = 20;

void Sender::Loop() {
  std::string item;
  while (q.trypop(&item)) {
    if (on_send && !on_send(&item)) continue;
    if (connection.SendStr(item.c_str()) < 0)
      break;
  }
  connection.ShutdownWrite();
}

void Receiver::Loop() {
  while (true) {
    char* data = connection.GetStr();
    if (!data) break;

    std::string item(data);
    delete[] data;

    if (on_receive && !on_receive(&item)) continue;
    q->push(std::move(item));
  }
  // Since the queue may be shared by different ECs, don't close it from here
}

BlockingQueue<std::string>& EnqueuedConnection::GetOutgoingQueue() {
  return sender.q;
}

BlockingQueue<std::string>& EnqueuedConnection::GetIncomingQueue() {
  return *receiver.q;
}

void EnqueuedConnection::Shutdown() {
  connection.ShutdownRead();
  sender.q.close();
}

void EnqueuedConnection::Join() {
  sender.Join();
  receiver.Join();
}


// Support methods

EnqueuedConnection::EnqueuedConnection(Connection&& c,
  BlockingQueue<std::string>& in_queue)
  : connection(std::move(c)), sender(connection), receiver(connection, &in_queue)
{
  sender.Start();
  receiver.Start();
}

EnqueuedConnection::~EnqueuedConnection() {
  Shutdown();
  sender.Join();
  receiver.Join();
}

Sender::Sender(Connection& c)
  : connection(c), t(), q(QUEUE_SIZE), on_send(nullptr)
{}

Receiver::Receiver(Connection& c, BlockingQueue<std::string>* in_queue)
  : connection(c), t(), q(in_queue), on_receive(nullptr)
{}

void Sender::Start() {
  t = std::thread(&Sender::Loop, this);
}

void Receiver::Start() {
  t = std::thread(&Receiver::Loop, this);
}

void Sender::Join() {
  if (t.joinable())
    t.join();
}

void Receiver::Join() {
  if (t.joinable())
    t.join();
}

void EnqueuedConnection::SetIncomingQueue(BlockingQueue<std::string>& in_queue) {
  receiver.q = &in_queue;
}
