#include "Lobby.h"
#include <thread>
#include "../common/blockingqueue.h"

void Lobby::Add(Connection&& c) {
  xxx.emplace_back(std::move(c));
  xxx.back().Start();

  // garbage collect dead xxx
}

Cola& Lobby::JoinGame(int id, Cola& outq) {}

void Lobby::Shutdown() {}

void Lobby::Join() {}
