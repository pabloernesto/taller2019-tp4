#include "EnqueuedConnection.h"

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
