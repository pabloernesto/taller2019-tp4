#include "image.h"
#include <string>
   
Image::Image(std::string imageName, SDL_Window* ventana,
        SDL_Renderer* renderer): 
        image(SDL_LoadBMP(imageName.c_str())), 
        texture(SDL_CreateTextureFromSurface(renderer, image)),
        x(0), y(0){
	if (this->image == NULL)
		SDL_ShowSimpleMessageBox(0, "Image init error", SDL_GetError(),
			ventana);
	if (texture == NULL)
		SDL_ShowSimpleMessageBox(0, "Texture init error",
			SDL_GetError(), ventana);
}

Image::~Image(){
	SDL_DestroyTexture(this->texture);
	SDL_FreeSurface(this->image);
}

void Image::render(SDL_Renderer* renderer){
    SDL_Rect dstrect = {0, 0, 640, 480};
    SDL_RenderCopy(renderer, this->texture, NULL, &dstrect);
}