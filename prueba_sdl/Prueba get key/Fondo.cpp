#include "Fondo.h"
#include <string>
   
Fondo::Fondo(std::string nombreImagen, SDL_Window* ventana,
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

Fondo::~Fondo(){
	SDL_DestroyTexture(this->textura);
	SDL_FreeSurface(this->imagen);
}

void Fondo::render(SDL_Renderer* renderer){
    SDL_Rect dstrect = {0, 0, 640, 480};
    SDL_RenderCopy(renderer, this->textura, NULL, &dstrect);
}