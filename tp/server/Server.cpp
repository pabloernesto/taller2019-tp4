#include "Server.h"
#include <thread>

void Server::Add(Connection&& c) {
  rooms.emplace_back(new ServerRoom(std::move(c), *this));
  rooms.back()->Start();

  // garbage collect dead rooms
}

void Server::JoinGame(int id, ServerRoom& player) {
  for (auto& game : games) {
    if (game->id != id) continue;
    game->AddPlayer(player);
    return;
  }
  throw std::runtime_error("Tratando de unirse a un juego que no existe");
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
      if ( ! (*it)->isRunning()){
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
}

void Server::notify(){
  this->notified = true;
}

int Server::NewGame() {
  // TODO: pass real track
  games.emplace_back(new Game(maxid++, ""));
  games.back()->Start();
  return games.back()->id;
}

void Server::Start(){
  collector_thread = std::thread(&Server::collectorLoop, this);
}

void Server::Shutdown() {
  this->quit = true;
  this->notified = true;
  this->cond_var.notify_one();
}

void Server::Join() {
  if (collector_thread.joinable()) 
    collector_thread.join();
}

Server::Server() : games(), maxid(0), rooms(), notified(false), quit(false){}
