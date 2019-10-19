#ifndef AUTO_H_
#define AUTO_H_
#include <SDL2/SDL.h>
#include <string>

class Auto{
private:
    SDL_Surface* imagen;
    SDL_Texture* textura;
    int x;
    int y;

public:
    Auto(std::string nombreImagen, SDL_Window* ventana,
        SDL_Renderer* renderer);
    ~Auto();

    void render(SDL_Renderer* renderer);
    void reactTo(SDL_Event &evento);

};

#endif