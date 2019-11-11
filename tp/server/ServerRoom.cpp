#include "ServerRoom.h"
#include "Server.h"
#include "Protocol.h"
#include "rapidjson/document.h"

static const int QUEUE_SIZE = 20;

void ServerRoom::HandleRequest(rapidjson::Document& req) {
  if (!req.HasMember("type"))
    ; // tirar un error
  std::string reqtype = req["type"].GetString();

  // List available games
  if (reqtype == "l") {
    auto&& json = ToJSON(server.GetGames());
    client.GetOutgoingQueue().push(std::move(json));
  
  // Join a game given an id
  } else if (reqtype == "j") {
    if (!req.HasMember("id"))
      ; // tirar un error
    int gameid = req["id"].GetInt();
    try {
      auto &incoming_queue = server.JoinGame(gameid, client.GetOutgoingQueue());
      // WARN: Race condition? What if client sends a message before SetIncomingQueue?
      client.SetIncomingQueue(incoming_queue);
      // Clear leftover messages
      client_messages.clear();
      quit = true;
    } catch (std::runtime_error e) {
      client.GetOutgoingQueue().push("{\"error\": \"no such game\"}");
    }
  }
}

void ServerRoom::Loop() {
  while (!quit) {
    std::string str;
    if (!client_messages.trypop(&str))
      ; // handle client disconnection

    rapidjson::Document d;
    d.Parse(str.c_str());

    HandleRequest(d);
  }
}

void ServerRoom::Start() {
  thread = std::thread(&ServerRoom::Loop, this);
}

void ServerRoom::Join() {
  client.Shutdown();
  if (thread.joinable())
    thread.join();
}

ServerRoom::ServerRoom(Connection&& c, Server& s)
  : quit(false), client_messages(QUEUE_SIZE),
  client(std::move(c), client_messages), thread(), server(s)
{}
