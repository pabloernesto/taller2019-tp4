#ifndef LOBBY_H_
#define LOBBY_H_

#include "../common/socket.h"
#include <vector>
#include <thread>

class Lobby {
  std::vector<Game> games;
  std::vector<Connection> clients;
  std::thread t;

  void Loop();

public:
  void Add(Connection&& c);

  void Start();
  void Shutdown();
  void Join();
};

#endif  // LOBBY_H_
