#ifndef x_H_
#define x_H_

#include "../common/socket.h"
#include <thread>
#include "Lobby.h"
#include "rapidjson/document.h"

class x {
  bool quit;
  Connection client;
  std::thread thread;
  Lobby& lobby;

  void HandleRequest(rapidjson::Document& req);
  void Loop();

public:
  void Start();
  void Join();

  x(Connection&& c, Lobby& l);
};

#endif // x_H_
