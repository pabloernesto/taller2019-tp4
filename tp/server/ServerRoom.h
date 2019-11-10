#ifndef SERVERROOM_H_
#define SERVERROOM_H_

#include "../common/socket.h"
#include "../common/blockingqueue.h"
#include "EnqueuedConnection.h"
#include <thread>
#include "Server.h"
#include "rapidjson/document.h"

class Server;

class ServerRoom {
  bool quit;
  BlockingQueue<std::string> client_messages;
  EnqueuedConnection client;
  std::thread thread;
  Server& server;

  void HandleRequest(rapidjson::Document& req);
  void Loop();

public:
  void Start();
  void Join();

  ServerRoom(Connection&& c, Server& s);
};

#endif // SERVERROOM_H_
