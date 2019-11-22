#ifndef SERVERROOM_H_
#define SERVERROOM_H_

#include "../common/socket.h"
#include "../common/blockingqueue.h"
#include "../common/EnqueuedConnection.h"
#include <thread>
#include <atomic>
#include "rapidjson/document.h"

class Server;

class ServerRoom {
  std::atomic<bool> quit;
  BlockingQueue<std::string> client_messages;
  std::thread thread;
  Server& server;

  void HandleRequest(rapidjson::Document& req);
  void Loop();

  void ListAvailableGames();
  void JoinGame(int gameid);
  void CreateGame();

public:
  EnqueuedConnection client;
  std::atomic<bool> disconnected;

  void reconnectPlayer();
  void ShutdownConnection();
  void Shutdown();
  void Start();
  void Join();

  ServerRoom(Connection&& c, Server& s);
};

#endif // SERVERROOM_H_
