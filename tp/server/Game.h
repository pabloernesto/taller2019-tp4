#ifndef GAME_H_
#define GAME_H_

#include "../common/Race.h"
#include "../common/blockingqueue.h"
#include "../common/EnqueuedConnection.h"
#include "Responsibility.h"
#include <thread>
#include <vector>
#include <string>
#include <atomic>
#include <memory>   // unique_ptr

typedef BlockingQueue<std::string> Cola;

class Game {
  std::unique_ptr<Race> race;
  std::thread update_thread;
  Cola in_queue;
  std::vector<Cola*> out_queues;
  std::atomic<bool> quit;
  std::unique_ptr<TaskHandler> handler_chain;

  void Loop();

public:
  int id;

  void AddPlayer(EnqueuedConnection& player);

  // Thread control methods
  void Start();
  void Shutdown();
  void Join();

  Game(int id, std::string track);
};

#endif  // GAME_H_
