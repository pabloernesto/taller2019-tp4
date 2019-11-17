#include "Server.h"
#include <thread>

void Server::Add(Connection&& c) {
  rooms.emplace_back(new ServerRoom(std::move(c), *this));
  rooms.back()->Start();

  // garbage collect dead rooms
}

void Server::JoinGame(int id, ServerRoom& player) {
  // Race condition: what if a game is removed while iterating the vector?
  for (auto& game : games) {
    if ( (game->id != id) || (game->isRunning()) || ( (!game->isRunning()) && (!game->isOnPreGameLoop()) ) ) 
      continue;
        // First case: Game doesn't exist.
        // Second case: Game already started.
        // Third case: Game finished and it's waiting for collectorLoop to remove him.
    game->AddPlayer(player);
    return;
  }
  throw std::runtime_error("Tratando de unirse a un juego que no existe o ya comenzo");
}

std::vector<std::unique_ptr<Game>>& Server::GetGames() {
  return games;
}

void Server::collectorLoop(){
  std::unique_lock<std::mutex> lock(this->mutex);
  while (!this->quit){
    while (!this->notified){
      this->cond_var.wait(lock);
    }
    auto it = this->games.begin();
    while (it != this->games.end()){
      if ( (! (*it)->isRunning()) && (! (*it)->isOnPreGameLoop())){
        (*it)->Join();
        it = this->games.erase(it);
      } else {
        it++;
      }
    }
    this->notified = false;
  }

  // Shutdown remaining games
  for (auto it = this->games.begin(); it != this->games.end(); it++){
    (*it)->Shutdown();
  }
  for (auto it = this->games.begin(); it != this->games.end(); it++){
    (*it)->Join();
  }

  // Shutdown server rooms
  for (auto it = this->rooms.begin(); it != this->rooms.end(); it++){
    (*it)->ShutdownConnection();
    (*it)->Shutdown();
  }
  for (auto it = this->rooms.begin(); it != this->rooms.end(); it++){
    (*it)->Join();
  }
}

void Server::notify() {
  std::lock_guard<std::mutex> lock(mutex);
  this->notified = true;
  cond_var.notify_one();
}

int Server::NewGame() {
  // TODO: pass real track
  games.emplace_back(new Game(maxid++, "", this->mutex, *this));
  games.back()->Start();
  return games.back()->id;
}

void Server::Start(){
  collector_thread = std::thread(&Server::collectorLoop, this);
}

void Server::Shutdown() {
  for (auto& game : games) game->Shutdown();
  for (auto& game : games) game->Join();

  this->quit = true;
  notify();
}

void Server::Join() {
  if (collector_thread.joinable())
    collector_thread.join();
}

Server::Server() : games(), maxid(0), rooms(), notified(false), quit(false){}
