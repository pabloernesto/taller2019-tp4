#ifndef TEXTPRINTER_H_
#define TEXTPRINTER_H_
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class TextPrinter {
  private:
    SDL_Color color;
    TTF_Font* font;

  public:
    TextPrinter(TTF_Font* font);
    void showMessage(std::string message, int size, int x, int y, SDL_Renderer* r);

};

#endif
