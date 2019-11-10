#ifndef SERVER_H_
#define SERVER_H_

#include "../common/socket.h"
#include <vector>
#include <thread>

typedef BlockingQueue<std::string> Cola;

class Server {
  std::vector<Game> games;
  std::vector<X> xxx;

public:
  void Add(Connection&& c);
  Cola& JoinGame(int id, Cola& outq);

  void Shutdown();
  void Join();
};

#endif  // SERVER_H_
