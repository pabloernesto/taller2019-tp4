#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char** argv)
{
	bool salir = false;
	SDL_Event evento;

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	SDL_Window* ventana = SDL_CreateWindow("Animacion",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640,
		480, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(ventana, -1, 0);
	SDL_Surface* imagen = IMG_Load("animacion.png");
	SDL_Texture* textura = SDL_CreateTextureFromSurface(renderer,
		imagen);

	while (!salir)
	{
		Uint32 ticks = SDL_GetTicks();
		Uint32 sprite = (ticks / 100) % 3;
		
		SDL_Rect srcrect = { sprite * 460, 0, 460, 1000 };
		SDL_Rect dstrect = { 0, 0, 250, 400 };
		SDL_PollEvent(&evento);

		switch (evento.type)
		{
		case SDL_QUIT:
			salir = true;
			break;
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, textura, &srcrect, &dstrect);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(textura);
	SDL_FreeSurface(imagen);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(ventana);
	IMG_Quit();
	SDL_Quit();

	return 0;
}
