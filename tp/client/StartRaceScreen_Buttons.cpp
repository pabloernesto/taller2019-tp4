#include "StartRaceScreen_Buttons.h"
#include "RaceScreen.h"
#include "StartRaceScreen.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>

/*****************
 * StartRaceWithoutAI
 *****************/

bool StartRaceWithoutAIButton::OnHandle(void* t) {
  // Start the race
  rapidjson::Document d(rapidjson::kObjectType);
  d.AddMember("type", "s", d.GetAllocator());
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  d.Accept(writer);
  context->race->SendToServer(std::string(buffer.GetString()));

  // Transition screens
  context->next_screen = new RaceScreen(
    window, renderer, context->race.release(), context->player_id, false);

  return false;
}

StartRaceWithoutAIButton::StartRaceWithoutAIButton(TaskHandler* next, SDL_Window* w,
  SDL_Renderer* r, SDL_Rect area, std::string text, TTF_Font* font,
  SDL_Color color, StartRaceScreen* context)
  : TextButton(next, w, r, area, text, font, color),
  context(context)
{}

/*****************
 * StartRaceWithAI
 *****************/

bool StartRaceWithAIButton::OnHandle(void* t) {
  // Start the race
  rapidjson::Document d(rapidjson::kObjectType);
  d.AddMember("type", "s", d.GetAllocator());
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  d.Accept(writer);
  context->race->SendToServer(std::string(buffer.GetString()));

  // Transition screens
  context->next_screen = new RaceScreen(
    window, renderer, context->race.release(), context->player_id, true);

  return false;
}

StartRaceWithAIButton::StartRaceWithAIButton(TaskHandler* next, SDL_Window* w,
  SDL_Renderer* r, SDL_Rect area, std::string text, TTF_Font* font,
  SDL_Color color, StartRaceScreen* context)
  : TextButton(next, w, r, area, text, font, color),
  context(context)
{}
