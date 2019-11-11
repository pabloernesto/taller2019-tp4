#ifndef SERVER_H_
#define SERVER_H_

#include "Game.h"
#include "ServerRoom.h"
#include "../common/socket.h"
#include <vector>
#include <thread>
#include <memory>   // unique_ptr

typedef BlockingQueue<std::string> Cola;

class Server {
  std::vector<Game> games;
  std::vector<std::unique_ptr<ServerRoom>> rooms;

public:
  void Add(Connection&& c);
  Cola& JoinGame(int id, Cola& outq);

  void Shutdown();
  void Join();
};

#endif  // SERVER_H_
