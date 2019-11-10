#ifndef x_H_
#define x_H_

#include "../common/socket.h"
#include "../common/blockingqueue.h"
#include "EnqueuedConnection.h"
#include <thread>
#include "Server.h"
#include "rapidjson/document.h"

class x {
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

  x(Connection&& c, Server& s);
};

#endif // x_H_
