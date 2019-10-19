#include "Auto.h"
#include <string>

#define TAMMOVIMIENTO 10
   
Auto::Auto(std::string nombreImagen, SDL_Window* ventana,
        SDL_Renderer* renderer): 
        imagen(SDL_LoadBMP(nombreImagen.c_str())), 
        textura(SDL_CreateTextureFromSurface(renderer, imagen)),
        x(0), y(0){
	if (this->imagen == NULL)
		SDL_ShowSimpleMessageBox(0, "Image init error", SDL_GetError(),
			ventana);
	if (textura == NULL)
		SDL_ShowSimpleMessageBox(0, "Texture init error",
			SDL_GetError(), ventana);
}

Auto::~Auto(){
	SDL_DestroyTexture(this->textura);
	SDL_FreeSurface(this->imagen);
}

void Auto::render(SDL_Renderer* renderer){
    SDL_Rect dstrect = { this->x * TAMMOVIMIENTO, 
        this->y * TAMMOVIMIENTO, 100, 200};
    SDL_RenderCopy(renderer, this->textura, NULL, &dstrect);
}

void Auto::reactTo(SDL_Event &evento){
    switch( evento.key.keysym.sym ){
        case SDLK_LEFT:
            this->x -= 1;
            break;
        case SDLK_RIGHT:
            this->x += 1;
            break;
        case SDLK_UP:
            this->y -= 1;
            break;
        case SDLK_DOWN:
            this->y += 1;
            break;
        default:
            break;
    }
}