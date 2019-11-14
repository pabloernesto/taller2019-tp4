#include "Game.h"
#include <chrono>   // std::chrono::system_clock, std::chrono::milliseconds
#include <thread>   // std::this_thread::sleep_for
#include "Protocol.h"
#include "ServerRoom.h"
#include "../common/RaceFabric.h"
#include "CarController.h"
#include "StartGameController.h"
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

    for (auto& carp : race->GetCars()) {
      auto&& json = ToJSON(*carp);
      for (auto& p : players)
        p->client.GetOutgoingQueue().push(std::string(json));
    }

    auto&& mods_json = ToJSON(race->getModifiers());
    for (auto& p : players)
      p->client.GetOutgoingQueue().push(std::string(mods_json));

    // Check if race ended.
    if (this->race->Ended()){
      // Sent the new condition and winner id to every client.
      auto&& json = ToJSON(*(this->race));
      for (auto p : players)
        p->client.GetOutgoingQueue().push(std::string(json));
      // Now what? How do i exit? How do i report the clients?
      this->quit = true; 
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
  running = false;
  // Aca deberia volver a donde?
}

void Game::preGameLoop(){
  while (!quit && !running) {
    // Read client messages
    std::queue<std::string> to_process;
    in_queue.swap(to_process);
    while (!to_process.empty()) {
      auto&& request = Parse(to_process.front());
      handler_chain->Handle(&request);
      to_process.pop();
    }
  }
  if (quit) return;

  // Realease all remaining messages, so games starts clean.
  std::queue<std::string> to_process;
  in_queue.swap(to_process);

  // Create controllers for every car
  handler_chain.reset();
  for (auto& car : race->GetCars())
    handler_chain.reset(new CarController(handler_chain.release(), *car));

  Loop();
}


void Game::AddPlayer(ServerRoom& player) {
  // Start broadcasting messages to player
  players.push_back(&player);

  // Add player car
  auto& car = race->AddNewCarToRace();

  // Add player id to player's messages
  const int playerid = car.GetId();
  player.client.OnReceive([playerid](std::string* msg){
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
  player.client.SetIncomingQueue(in_queue);

  // Tell player which car is his
  player.client.GetOutgoingQueue().push(
    "{\"id\": " + std::to_string(playerid) + "}"
  );
}

Track& Game::GetTrack() {
  return race->GetTrack();
}


void Game::startGame(int user_id){
  id_started.insert(user_id);
  if (players.size() == id_started.size())
    running = true;
}

bool Game::isRunning(){
  return (!this->running) && (this->quit);
}

// Thread control methods

void Game::Start() {
  update_thread = std::thread(&Game::preGameLoop, this);
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
  update_thread(), in_queue(QUEUE_SIZE), players(), quit(false),
  running(false), handler_chain(), id(id)
{
  handler_chain.reset(new StartGameController(NULL, (*this)));
}