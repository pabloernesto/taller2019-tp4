#include <iostream>
#include "../common/socket.h"
#include "../common/blockingqueue.h"
#include "EnqueuedConnection.h"
#include <string>
#include <thread>

int main(int argc, char **argv) {
  Listener listener("1234");
  BlockingQueue<std::string> q(20);

  std::thread acceptor_thread([&listener, &q]() {
    while (true) {
      try {
        EnqueuedConnection connection(listener.Accept(), q);
        std::string str;
        while (connection.GetIncomingQueue().trypop(&str))
          std::cout << str;

      } catch (std::runtime_error e) {
        break;
      }
    }
  });

  while (std::cin.peek() != EOF) {
    char c;
    std::cin.get(c);
    if (c == 'q') break;
  }

  listener.Shutdown();
  q.close();
  acceptor_thread.join();
}
