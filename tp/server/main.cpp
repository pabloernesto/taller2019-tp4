#include <iostream>
#include "../common/socket.h"
#include "Lobby.h"
#include <thread>

int main(int argc, char **argv) {
  Listener listener("1234");
  Lobby lobby;

  std::thread acceptor_thread([&listener, &lobby]() {
    while (true) {
      try { lobby.Add(listener.Accept()); }
      catch (std::runtime_error e) { break; }
    }
  });

  while (std::cin.peek() != EOF) {
    char c;
    std::cin.get(c);
    if (c == 'q') break;
  }

  listener.Shutdown();
  acceptor_thread.join();

  lobby.Shutdown();
  lobby.Join();
}
