#include "Lobby.h"
#include <thread>

void Lobby::Add(Connection&& c) {
  clients.push_back(std::move(c));
}

void Lobby::Start() {
  t = std::thread(&Lobby::Loop, this);
}

void Lobby::Loop() {
}
