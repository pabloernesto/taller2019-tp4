#ifndef GAME_H_
#define GAME_H_

#include "../common/Race.h"
#include "../common/blockingqueue.h"
#include "../common/EnqueuedConnection.h"
#include "../common/Responsibility.h"
#include "ServerRoom.h"
#include <thread>
#include <vector>
#include <string>
#include <atomic>
#include <memory>   // unique_ptr
#include <unordered_set>

typedef BlockingQueue<std::string> Cola;

class Game {
  std::unique_ptr<Race> race;
  std::thread update_thread;
  Cola in_queue;
  std::vector<ServerRoom*> players;
  std::atomic<bool> quit;
  bool running;
  std::unique_ptr<TaskHandler> handler_chain;
  std::unordered_set<int> id_started;

  void Loop();
  void preGameLoop();

public:
  int id;

  void AddPlayer(ServerRoom& player);
  Track& GetTrack();
  void startGame(int user_id);
  bool didIdStarted(int user_id);
  bool isRunning();

  // Thread control methods
  void Start();
  void Shutdown();
  void Join();

  Game(int id, std::string track);
};

#endif  // GAME_H_
