#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include "Auto.h"

int main(int argc, char** argv){
	bool salir = false;
	SDL_Event evento;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return 1;
	}

	SDL_Window* ventana = SDL_CreateWindow("Prueba de SDL",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	if (ventana == NULL)
		SDL_ShowSimpleMessageBox(0, "Window init error", SDL_GetError(),
			ventana);
	SDL_Renderer* renderer = SDL_CreateRenderer(ventana, -1, 0);
	if (renderer == NULL)
		SDL_ShowSimpleMessageBox(0, "Renderer init error",
			SDL_GetError(), ventana);
	
    std::string nombre = "pitstop_car_1.bmp";
    Auto automovil(nombre, ventana, renderer);
    
    
    while( !salir ){
        SDL_WaitEvent(&evento);

		switch (evento.type)
		{
		case SDL_QUIT:
			salir = true;
			break;
		}
		
        SDL_RenderClear(renderer);
        automovil.reactTo(evento);
        automovil.render(renderer);
		SDL_RenderPresent(renderer);
    }
    
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(ventana);
	SDL_Quit();

	return 0;
}