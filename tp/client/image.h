#ifndef IMAGE_H_
#define IMAGE_H_
#include <SDL2/SDL.h>
#include <string>

class Image{
private:
    SDL_Surface* image;
    SDL_Texture* texture;
    int x;
    int y;

public:
    Image(std::string imageName, SDL_Window* window,
        SDL_Renderer* renderer);
    ~Image();

    void render(SDL_Renderer* renderer);
};

#endif