#include "x.h"
#include "rapidjson/document.h"

static const int QUEUE_SIZE = 20;

void x::HandleRequest(rapidjson::Document& req) {
  if (!req.HasMember("type"))
    ; // tirar un error
  std::string reqtype = req["type"].GetString();

  // List available games
  if (reqtype == "l") {
    client.GetOutgoingQueue().push("[1, 2, 3]");
  
  // Join a game given an id
  } else if (reqtype == "j") {
    if (!req.HasMember("id"))
      ; // tirar un error
    int gameid = req["id"].GetInt();
    auto &incoming_queue = server.JoinGame(gameid, client.GetOutgoingQueue());
    client.SetIncomingQueue(incoming_queue);
    // Clear leftover messages
    client_messages.clear();
    quit = true;
  }
}

void x::Loop() {
  while (!quit) {
    std::string str;
    bool popped = client_messages.trypop(&str);

    rapidjson::Document d;
    d.Parse(str.c_str());

    HandleRequest(d);
  }
}

void x::Start() {
  thread = std::thread(&x::Loop, this);
}

void x::Join() {
  client.Shutdown();
  if (thread.joinable())
    thread.join();
}

x::x(Connection&& c, Server& s)
  : quit(false), client_messages(QUEUE_SIZE),
  client(std::move(c), client_messages), thread(), server(s)
{}
