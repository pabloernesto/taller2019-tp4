#include "Server.h"
#include <thread>
#include "../common/EnqueuedConnection.h"

void Server::Add(Connection&& c) {
  rooms.emplace_back(new ServerRoom(std::move(c), *this));
  rooms.back()->Start();

  // garbage collect dead rooms
}

void Server::JoinGame(int id, EnqueuedConnection& player) {
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

int Server::NewGame() {
  // TODO: pass real track
  games.emplace_back(new Game(maxid++, ""));
  return games.back()->id;
}

void Server::Shutdown() {}

void Server::Join() {}

Server::Server() : games(), maxid(0), rooms() {
  NewGame();
}
