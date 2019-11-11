#include "Game.h"
#include <chrono>   // std::chrono::system_clock, std::chrono::milliseconds
#include <thread>   // std::this_thread::sleep_for
#include "Protocol.h"
#include "CarController.h"
#include <memory>

static const int FRAMERATE = 60;
static const int QUEUE_SIZE = 50;

void Game::Loop() {
  const auto rate = std::chrono::milliseconds(1000 / FRAMERATE);
  auto time1 = std::chrono::system_clock::now();

  while (!quit) {
    // Read client messages
    std::queue<std::string> to_process;
    in_queue.swap(to_process);
    while (!to_process.empty()) {
      auto&& request = Parse(to_process.front());
      handler_chain->Handle(&request);
      to_process.pop();
    }

    race.Step();

    // TODO: send client responses
    // TODO: send powerup information
    for (auto& carp : race.GetCars()) {
      auto&& json = ToJSON(*carp);
      for (auto& q : out_queues)
        q->push(std::move(json));
    }

    // Frame rate limiting
    const auto time2 = std::chrono::system_clock::now();
    auto rest = rate - (time2 - time1);
    if (rest.count() < 0) {
      const auto behind = -rest;
      const auto lost = behind - behind % rate;
      rest = rate - behind % rate;
      time1 += lost;
    }

    time1 += rate;
    std::this_thread::sleep_for(rest);
  }
}

Cola& Game::AddPlayer(Cola& player_queue) {
  out_queues.push_back(&player_queue);
  TaskHandler* handler = handler_chain.release();
  handler_chain.reset(new CarController(handler, race.AddNewCarToRace()));
  return in_queue;
}


// Thread control methods

void Game::Start() {
  update_thread = std::thread(&Game::Loop, this);
}

void Game::Shutdown() {
  quit = true;
}

void Game::Join() {
  if (update_thread.joinable()) update_thread.join();
}

// TODO: pass real track
Game::Game(int id, std::string track)
  : race("6 9 666662004204661661163005661166666661162004661305663005 ", 1),
  update_thread(), in_queue(QUEUE_SIZE), out_queues(), quit(false),
  handler_chain(), id(id)
{
  // TODO: populate handler_chain()
  handler_chain.reset(NULL);
}