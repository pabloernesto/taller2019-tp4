#include "Server.h"
#include <thread>
#include "../common/blockingqueue.h"

void Server::Add(Connection&& c) {
  rooms.emplace_back(new ServerRoom(std::move(c), *this));
  rooms.back()->Start();

  // garbage collect dead rooms
}

Cola& Server::JoinGame(int id, Cola& outq) {}

void Server::Shutdown() {}

void Server::Join() {}
