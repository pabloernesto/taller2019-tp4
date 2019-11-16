#include "RaceScreen_Buttons.h"
#include "RaceScreen.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>


bool StartRaceButton::OnHandle(void* t) {
  rapidjson::Document d(rapidjson::kObjectType);
  d.AddMember("type", "s", d.GetAllocator());
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  d.Accept(writer);
  context->race->SendToServer(std::string(buffer.GetString()));

  return false;
}

StartRaceButton::StartRaceButton(TaskHandler* next, SDL_Window* w,
  SDL_Renderer* r, SDL_Rect area, std::string text, TTF_Font* font,
  SDL_Color color, RaceScreen* context)
  : TextButton(next, w, r, area, text, font, color),
  context(context)
{}
