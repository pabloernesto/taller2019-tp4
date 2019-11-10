#ifndef GAME_H_
#define GAME_H_

#include "../common/Race.h"
#include "../common/blockingqueue.h"
#include "Responsibility.h"
#include <thread>
#include <vector>
#include <string>
#include <atomic>

typedef BlockingQueue<std::string> Cola;

class Game {
  Race race;
  std::thread update_thread;
  Cola in_queue;
  std::vector<Cola&> out_queues;
  std::atomic<bool> quit;
  std::unique_ptr<TaskHandler> handler_chain;

  void Loop();

public:
  Cola& AddPlayer(Cola& player_queue);

  // Thread control methods
  void Start();
  void Shutdown();
  void Join();

  Game(std::string track);
};

#endif  // GAME_H_
