#include <iostream>
#include "../common/socket.h"
#include "Server.h"
#include <thread>
#include "Configuration.h"

Configuration configuration("Configuracion/config.json");

int main(int argc, char **argv) {
  Listener listener("1234");
  Server server;
  server.Start();
  
  std::thread acceptor_thread([&listener, &server]() {
    while (true) {
      try { server.Add(listener.Accept()); }
      catch (std::runtime_error& e) { break; }
    }
  });

  while (std::cin.peek() != EOF) {
    char c;
    std::cin.get(c);
    if (c == 'q') break;
  }

  listener.Shutdown();
  acceptor_thread.join();
  std::cerr << "Acceptor thread joined\n";
  server.Shutdown();
  std::cerr << "Server shutdown\n";
  server.Join();
  std::cerr << "Server joined\n";
}
