#include "Server.h"
#include <thread>
#include "../common/blockingqueue.h"

void Server::Add(Connection&& c) {
  rooms.emplace_back(new ServerRoom(std::move(c), *this));
  rooms.back()->Start();

  // garbage collect dead rooms
}

Cola& Server::JoinGame(int id, Cola& outq) {
  for (auto& game : games) {
    if (game.id != id) continue;
    return game.AddPlayer(outq);
  }
  throw std::runtime_error("Tratando de unirse a un juego que no existe");
}

std::vector<Game>& Server::GetGames() {
  return games;
}

void Server::Shutdown() {}

void Server::Join() {}
