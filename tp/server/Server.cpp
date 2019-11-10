#include "Server.h"
#include <thread>
#include "../common/blockingqueue.h"

void Server::Add(Connection&& c) {
  xxx.emplace_back(std::move(c));
  xxx.back().Start();

  // garbage collect dead xxx
}

Cola& Server::JoinGame(int id, Cola& outq) {}

void Server::Shutdown() {}

void Server::Join() {}
