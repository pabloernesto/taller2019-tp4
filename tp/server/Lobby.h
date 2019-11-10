#ifndef LOBBY_H_
#define LOBBY_H_

#include "../common/socket.h"
#include <vector>
#include <thread>

typedef BlockingQueue<std::string> Cola;

class Lobby {
  std::vector<Game> games;
  std::vector<X> xxx;

public:
  void Add(Connection&& c);
  Cola& JoinGame(int id, Cola& outq);

  void Shutdown();
  void Join();
};

#endif  // LOBBY_H_
