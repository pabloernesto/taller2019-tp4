#include <iostream>
#include "../common/socket.h"
#include "../common/blockingqueue.h"
#include "EnqueuedConnection.h"
#include <string>
#include <thread>

int main(int argc, char **argv) {
  Listener listener("1234");
  BlockingQueue<std::string> q(20);
  std::vector<std::unique_ptr<EnqueuedConnection>> connections;

  std::thread acceptor_thread([&listener, &q, &connections]() {
    while (true) {
      try {
        connections.emplace_back(new EnqueuedConnection(listener.Accept(), q));

      } catch (std::runtime_error e) {
        break;
      }
    }
  });

  std::thread writer_thread([&q]() {
    std::string s;
    while (q.trypop(&s))
      std::cout << s;
  });

  while (std::cin.peek() != EOF) {
    char c;
    std::cin.get(c);
    if (c == 'q') break;
  }

  listener.Shutdown();
  acceptor_thread.join();

  q.close();
  writer_thread.join();
}
