#include "EnqueuedConnection.h"

static const int QUEUE_SIZE = 20;

void Sender::Loop() {
  while (q.isPopable()) {
    auto&& item = q.pop();
    if (connection.SendStr(item.c_str()) < 0)
      break;
  }
  connection.ShutdownWrite();
}

void Receiver::Loop() {
  while (true) {
    char* data = connection.GetStr();
    if (!data)
      break;

    q.push(std::string(data));
    delete[] data;
  }
  q.close();
}

void EnqueuedConnection::Push(std::string&& s) {
  sender.q.push(std::move(s));
}

bool EnqueuedConnection::IsPopable() {
  return receiver.q.isPopable();
}

std::string EnqueuedConnection::Pop() {
  return receiver.q.pop();
}

void EnqueuedConnection::Shutdown() {
  connection.ShutdownRead();
  sender.q.close();
}



// Support methods

EnqueuedConnection::EnqueuedConnection(Connection&& c)
  : connection(std::move(c)), sender(connection), receiver(connection)
{
  sender.Start();
  receiver.Start();
}

EnqueuedConnection::~EnqueuedConnection() {
  Shutdown();
  sender.Join();
  receiver.Join();
}

Sender::Sender(Connection& c) : connection(c), t(), q(QUEUE_SIZE) {}

Receiver::Receiver(Connection& c) : connection(c), t(), q(QUEUE_SIZE) {}

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
