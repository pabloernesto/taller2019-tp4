#include "Protocol.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "../common/Car.h"
#include "Game.h"

rapidjson::Document Parse(std::string& x) {
  rapidjson::Document d;
  d.Parse(x.c_str());
  return d;
}

std::string ToJSON(Car& x) {
  rapidjson::Document d(rapidjson::kObjectType);
  d.AddMember("type", "car", d.GetAllocator());
  d.AddMember("id", x.GetId(), d.GetAllocator());
  d.AddMember("position.x", x.GetPosition().x, d.GetAllocator());
  d.AddMember("position.y", x.GetPosition().y, d.GetAllocator());
  d.AddMember("angle", x.GetAngle(), d.GetAllocator());
  d.AddMember("size.x", x.GetSize().x , d.GetAllocator());
  d.AddMember("size.y", x.GetSize().y , d.GetAllocator());
  d.AddMember("dead", x.isDead(), d.GetAllocator());
  // TODO: get life

  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  d.Accept(writer);

  return std::string(buffer.GetString());
}

std::string ToJSON(std::vector<std::unique_ptr<Modifier>>& x) {
  rapidjson::Document d(rapidjson::kObjectType);
  d.AddMember("type", "modifier", d.GetAllocator());

  rapidjson::Value list(rapidjson::kArrayType);
  for (auto& modifier : x) {
    rapidjson::Value node(rapidjson::kObjectType);
    node.AddMember("position.x", modifier->GetPosition().x, d.GetAllocator());
    node.AddMember("position.y", modifier->GetPosition().y, d.GetAllocator());
    node.AddMember("size.x", modifier->GetSize().x, d.GetAllocator());
    node.AddMember("size.y", modifier->GetSize().y, d.GetAllocator());
    rapidjson::Value type(modifier->getType().c_str(), d.GetAllocator());
    node.AddMember("modifier.type", type, d.GetAllocator());

    list.PushBack(node.Move(), d.GetAllocator());
  }

  d.AddMember("data", list.Move(), d.GetAllocator());

  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  d.Accept(writer);

  return std::string(buffer.GetString());
}

std::string ToJSON(std::vector<std::unique_ptr<Game>>& x) {
  rapidjson::Document d(rapidjson::kArrayType);
  for (auto& game : x) {
    rapidjson::Value race_node(rapidjson::kObjectType);
    race_node.AddMember("id", game->id, d.GetAllocator());

    rapidjson::Value track(rapidjson::kArrayType);
    for (auto& piece_ptr : game->GetTrack().getTrackPieces()) {
      rapidjson::Value piece_json(rapidjson::kObjectType);
      piece_json
        .AddMember("type", piece_ptr->getTrackType(), d.GetAllocator())
        .AddMember("size.x", piece_ptr->GetSize()[0], d.GetAllocator())
        .AddMember("size.y", piece_ptr->GetSize()[1], d.GetAllocator())
        .AddMember("pos.x", piece_ptr->GetPosition()[0], d.GetAllocator())
        .AddMember("pos.y", piece_ptr->GetPosition()[1], d.GetAllocator());
      track.PushBack(piece_json.Move(), d.GetAllocator());
    }

    race_node.AddMember("track", track.Move(), d.GetAllocator());
    d.PushBack(race_node.Move(), d.GetAllocator());
  }

  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  d.Accept(writer);

  return std::string(buffer.GetString());
}

std::string ToJSON(Race& x){
  rapidjson::Document d(rapidjson::kObjectType);
  
  d.AddMember("type", "race", d.GetAllocator());
  d.AddMember("ended", x.Ended(), d.GetAllocator());
  d.AddMember("winner_id", x.GetIdWinnerCar(), d.GetAllocator());
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  d.Accept(writer);

  return std::string(buffer.GetString());
}