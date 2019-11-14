#ifndef SERVER_H_
#define SERVER_H_

#include "Game.h"
#include "ServerRoom.h"
#include "../common/socket.h"
#include <vector>
#include <thread>
#include <atomic>
#include <memory>   // unique_ptr

class Server{
  std::vector<std::unique_ptr<Game>> games;
  int maxid;
  std::vector<std::unique_ptr<ServerRoom>> rooms;
  std::thread collector_thread;
  std::mutex mutex;
  std::condition_variable cond_var;
  bool notified;
  std::atomic<bool> quit;

private:
  void collectorLoop();

public:
  void Add(Connection&& c);
  void JoinGame(int id, ServerRoom& player);
  // Instantiate a race. Returns game id.
  int NewGame();
  void notify();

  std::vector<std::unique_ptr<Game>>& GetGames();


  // Thread control methods
  void Shutdown();
  void Join();
  void Start();

  Server();
};

#endif  // SERVER_H_
