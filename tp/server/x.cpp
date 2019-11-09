#include "x.h"
#include "rapidjson/document.h"

void x::HandleRequest(rapidjson::Document& req) {
  if (!req.HasMember("type"))
    ; // tirar un error
  std::string reqtype = req["type"].GetString();

  // List available games
  if (reqtype == "l") {
    client.SendStr("[1, 2, 3]");
  
  // Join a game given an id
  } else if (reqtype == "j") {
    if (!req.HasMember("id"))
      ; // tirar un error
    int gameid = req["id"].GetInt();
    lobby.JoinGame(gameid, client);
    quit = true;
  }
}

void x::Loop() {
  while (!quit) {
    char *data = client.GetStr();
    if (!data) ; // handle error

    rapidjson::Document d;
    d.Parse(data);
    delete[] data;

    HandleRequest(d);
  }
}

void x::Start() {
  thread = std::thread(&x::Loop, this);
}

void x::Join() {
  if (thread.joinable())
    thread.join();
}

x::x(Connection&& c, Lobby& l)
  : quit(false), client(std::move(c)), lobby(l)
{}
