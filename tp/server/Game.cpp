#include "Game.h"
#include <chrono>   // std::chrono::system_clock, std::chrono::milliseconds
#include <thread>   // std::this_thread::sleep_for
#include "Protocol.h"
#include "ServerRoom.h"
#include "RaceFabric.h"
#include "CarController.h"
#include "StartGameController.h"
// #include <iostream>
#include <memory>
#include <string>
#include <sys/types.h> //For directories
#include <dirent.h> //For directories
#include <dlfcn.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

static const int FRAMERATE = 60;
static const int QUEUE_SIZE = 50;
static const int MODS_TIME_SEC = 5;
static const int MODS_FRAMES = MODS_TIME_SEC * FRAMERATE;

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

    this->executeMods();

    race->Step();

    // TODO: handle all notifications with a single document
    for (auto& carp : race->GetCars()) {
      auto&& json = ToJSON(*carp);
      Broadcast(json);
    }

    auto&& mods_json = ToJSON(race->getModifiers());
    Broadcast(mods_json);

    // Check if race ended.
    if (this->race->Ended()){
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
  this->closeModsLibraries();
  running = false;
  this->reconnectPlayersToServerRoom();
  this->server.notify();
}

void Game::closeModsLibraries(){
  for (auto it = this->mods_shared_libs.begin(); this->mods_shared_libs.end(); it++){
    dlclose((*it));
  }
}

void Game::executeMods(){
  
  if (this->frame_counter_mods == MODS_FRAMES ){
    std::vector<CarModInterface*> cars_interface;
    for (auto it = this->race->GetCars().begin(); it != this->race->GetCars().end(); it++){
      cars_interface.push_back((*it).get());
    }
    for (auto it = this->mods.begin(); it != this->mods.end(); it++){
      // std::cout << "Before the disaster\n";
      (*it)->execute(this->race.get(), cars_interface);
      // std::cout << "After the disaster\n";
    }
    this->frame_counter_mods = 0;
  } else {
    this->frame_counter_mods += 1;
  }
}

void Game::reconnectPlayersToServerRoom(){
  for (auto it = this->players.begin(); it != this->players.end(); it++){
    (*it)->reconnectPlayer();
  }
  for (auto it = this->players.begin(); it != this->players.end(); it++){
    (*it)->Join();
  }
  for (auto it = this->players.begin(); it != this->players.end(); it++){
    (*it)->Start();
  }
  // Send the end of the race and winner id to every client.
  auto&& json = ToJSON(*(this->race));
  Broadcast(json);
}

void Game::Broadcast(std::string& msg) {
  for (auto it = players.begin(); it != players.end(); )
    try {
      (*it)->client.GetOutgoingQueue().push(std::string(msg));
      it++;
    } catch (std::runtime_error& e) {
      // TODO: mark room for garbage collection
      // TODO: remove controller from handler_chain
      it = players.erase(it);
    }
}

void Game::preGameLoop(){
  while (!quit && !running) {
    // Read client messages
    std::string str;
    if (in_queue.trypop(&str)) {
      auto&& request = Parse(str);
      handler_chain->Handle(&request);
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
    d.AddMember("type", "join", d.GetAllocator());
    d.AddMember("id", playerid, d.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);

    *msg = buffer.GetString();
    return true;
  });

  // Start accepting player messages
  player.client.SetIncomingQueue(in_queue);

  // Send player the id of his car and the track's shape
  rapidjson::Document d(rapidjson::kObjectType);
  d.AddMember("id", playerid, d.GetAllocator());
  AddMember(d, "track", race->GetTrack());
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  d.Accept(writer);
  player.client.GetOutgoingQueue().push(
    std::string(buffer.GetString())
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
  return (this->running) && (!this->quit);
}

bool Game::isOnPreGameLoop(){
  return (!quit) && (!running);
}

// Thread control methods

void Game::Start() {
  update_thread = std::thread(&Game::preGameLoop, this);
}

void Game::Shutdown() {
  quit = true;
  for (auto& p : players) p->client.Shutdown();
  in_queue.close();
}

void Game::Join() {
  if (update_thread.joinable()) update_thread.join();
}

// TODO: pass real track
Game::Game(int id, std::string track, std::mutex& mutex, Server& server)
  : race(RaceFabric::makeRace1()),
  update_thread(), in_queue(QUEUE_SIZE), players(), quit(false),
  running(false), handler_chain(), mutex(mutex), server(server), 
  frame_counter_mods(0), id(id)
{
  handler_chain.reset(new StartGameController(NULL, (*this)));
  
  // Load plugins
  DIR* plugins_dir = opendir("Plugins");
  struct dirent* ent = readdir(plugins_dir);
  Mod* (*create)();
  void* shared_lib;
  while (ent != NULL){
    // std::cout << "About to search for plugins\n";
    std::string file = "./Plugins/" + std::string(ent->d_name);        
    if (file.substr(file.size()- 3) != ".so"){
      ent = readdir(plugins_dir);
      continue;
    }
    // std::cout << "Found a library\n";
    // std::cout << "Library name: " << file << "\n";
    shared_lib = dlopen(file.c_str(), RTLD_NOW);
    char* err = dlerror();
    if (!shared_lib){
      throw std::runtime_error(std::string(err));
    }
    // Destroy hace falta o no...?
    // Mod* (*destroy)(Mod*)
    
    create = (Mod* (*)())dlsym(shared_lib, "create");
    this->mods.emplace_back(create());
    //dlclose(shared_lib); //Puedo cerrar la libreria? O no?
    this->mods_shared_libs.push_back(shared_lib);
    ent = readdir(plugins_dir);
  }

  closedir(plugins_dir);
  
}
