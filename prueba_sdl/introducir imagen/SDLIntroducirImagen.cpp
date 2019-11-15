#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char** argv)
{
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
  SDL_Surface* imagen = SDL_LoadBMP("pitstop_car_1.bmp");
  if (imagen == NULL)
    SDL_ShowSimpleMessageBox(0, "Image init error", SDL_GetError(),
      ventana);
  SDL_Texture* textura = SDL_CreateTextureFromSurface(renderer, imagen);
  if (textura == NULL)
    SDL_ShowSimpleMessageBox(0, "Texture init error",
      SDL_GetError(), ventana);

  printf("antes del while\n");
  while (!salir){
    SDL_WaitEvent(&evento);

    if (evento.type == SDL_QUIT){
      salir = true;
      break;
    }

    SDL_Rect dstrect = { 5, 5, 320, 400 };
    printf("va a hacer el copy\n");
    SDL_RenderCopy(renderer, textura, NULL, &dstrect);
    printf("termino el copy\n");
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(textura);
  SDL_FreeSurface(imagen);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(ventana);
  SDL_Quit();

  return 0;
}
