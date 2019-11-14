#ifndef SERVER_H_
#define SERVER_H_

#include "Game.h"
#include "ServerRoom.h"
#include "../common/socket.h"
#include <vector>
#include <thread>
#include <memory>   // unique_ptr

class Server {
  std::vector<std::unique_ptr<Game>> games;
  int maxid;
  std::vector<std::unique_ptr<ServerRoom>> rooms;

public:
  void Add(Connection&& c);
  void JoinGame(int id, ServerRoom& player);
  // Instantiate a race. Returns game id.
  int NewGame();

  std::vector<std::unique_ptr<Game>>& GetGames();

  void Shutdown();
  void Join();

  Server();
};

#endif  // SERVER_H_
