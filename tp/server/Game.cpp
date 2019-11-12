#include "Game.h"
#include <chrono>   // std::chrono::system_clock, std::chrono::milliseconds
#include <thread>   // std::this_thread::sleep_for
#include "Protocol.h"
#include "../common/RaceFabric.h"
#include "CarController.h"
#include <memory>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

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

    race->Step();

    // TODO: send client responses
    // TODO: send powerup information
    for (auto& carp : race->GetCars()) {
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

void Game::AddPlayer(EnqueuedConnection& player) {
  // Start broadcasting messages to player
  out_queues.push_back(&player.GetOutgoingQueue());

  // Add player car, and car controller
  TaskHandler* handler = handler_chain.release();
  handler_chain.reset(new CarController(handler, race->AddNewCarToRace()));

  // Add player id to player's messages
  const int playerid = out_queues.size();
  player.OnReceive([playerid](std::string* msg){
    rapidjson::Document d;
    d.Parse(msg->c_str());
    d.AddMember("id", playerid, d.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);

    *msg = buffer.GetString();
    return true;
  });

  // Start accepting player messages
  player.SetIncomingQueue(in_queue);
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
  : race(RaceFabric::makeRace1()),
  update_thread(), in_queue(QUEUE_SIZE), out_queues(), quit(false),
  handler_chain(), id(id)
{
  // TODO: populate handler_chain()
  handler_chain.reset(NULL);
}