#include "TextPrinter.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../common/Configuration.h"

#define FONT "MAKISUPA.TTF"

extern Configuration configuration;

TextPrinter::TextPrinter(TTF_Font* font) : color({255, 255, 255}),
  font(font) {}

void TextPrinter::showMessage(std::string message, int size, int x, int y, SDL_Renderer* r){
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, message.c_str(), color);
  SDL_Texture* Message = SDL_CreateTextureFromSurface(r, surfaceMessage);
  int width = size * (int)message.size();
  SDL_Rect Message_rect = {x - width/2, y - size/2, width, size};

  SDL_RenderCopyEx(r, Message, NULL, &Message_rect, 0, NULL, SDL_FLIP_NONE);
  SDL_DestroyTexture(Message);
  SDL_FreeSurface(surfaceMessage);
}