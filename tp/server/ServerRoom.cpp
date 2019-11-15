#include "ServerRoom.h"
#include "Server.h"
#include "Protocol.h"
#include "rapidjson/document.h"

static const int QUEUE_SIZE = 20;

void ServerRoom::HandleRequest(rapidjson::Document& req) {
  if (!req.HasMember("type"))
    ; // tirar un error
  std::string reqtype = req["type"].GetString();

  if (reqtype == "l") ListGames();
  else if (reqtype == "j")
    try
      { JoinGame(req["id"].GetInt()); }
    catch (std::runtime_error& e)
      { client.GetOutgoingQueue().push("{\"error\": \"no such game\"}"); }
  else if (reqtype == "c") CreateGame();
}

void ServerRoom::ListGames() {
  auto&& json = ToJSON(server.GetGames());
  client.GetOutgoingQueue().push(std::move(json));
}

void ServerRoom::JoinGame(int gameid) {
  server.JoinGame(gameid, *this);
  client_messages.clear();  // Clear leftover messages
  quit = true;
}

void ServerRoom::CreateGame() {
  int gameid = server.NewGame();
  server.JoinGame(gameid, *this);
  client_messages.clear();    // Clear leftover messages
  quit = true;
}

void ServerRoom::reconnectPlayer(){
  this->client.SetIncomingQueue(this->client_messages);
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

void ServerRoom::Shutdown(){
  client.Shutdown();
}

void ServerRoom::Join() {
  if (thread.joinable())
    thread.join();
}

ServerRoom::ServerRoom(Connection&& c, Server& s)
  : quit(false), client_messages(QUEUE_SIZE),
  thread(), server(s), client(std::move(c), client_messages)
{}
