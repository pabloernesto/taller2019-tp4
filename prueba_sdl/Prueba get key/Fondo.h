#ifndef FONDO_H_
#define FONDO_H_
#include <SDL2/SDL.h>
#include <string>

class Fondo{
private:
    SDL_Surface* imagen;
    SDL_Texture* textura;
    int x;
    int y;

public:
    Fondo(std::string nombreImagen, SDL_Window* ventana,
        SDL_Renderer* renderer);
    ~Fondo();

    void render(SDL_Renderer* renderer);
};

#endif