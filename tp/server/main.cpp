#include <iostream>
#include "../common/socket.h"
#include "EnqueuedConnection.h"
#include <string>
#include <thread>

int main(int argc, char **argv) {
  Listener listener("1234");

  std::thread acceptor_thread([&listener]() {
    while (true) {
      try {
        EnqueuedConnection connection(listener.Accept());
        std::string str;
        while (connection.Pop(&str)) std::cout << str;

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
  acceptor_thread.join();
}
