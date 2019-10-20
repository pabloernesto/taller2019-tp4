#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include <memory>     // unique_ptr
#include <iostream>   // cout
#include "Car.h"

const float32 timestep = 1 / 60.0;
const int32 velocityIterations = 8;
const int32 positionIterations = 3;

typedef struct {
  int x;
  int y;
} pixel_vect_s;

const int PIXELS_PER_METER = 10;
pixel_vect_s MKStoPixelTransform(const b2Vec2& vector) {
  pixel_vect_s v {
    PIXELS_PER_METER * vector.x,
    PIXELS_PER_METER * vector.y
  };
  return v;
}

int main(int argc, char **argv) {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window *window = SDL_CreateWindow(
    "Prueba auto",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // x and y
    640, 480,                                       // Width and Height
    SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

  // Setup physics
  b2Vec2 gravity(0, 0);
  b2World world(gravity);

  Car car;
  car.Place(world, (b2Vec2){0, 0});
  car.GasOn();

  SDL_Surface* img = SDL_LoadBMP("../prueba_sdl/introducir imagen/pitstop_car_1.bmp");
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img);

  // Simulation loop
  for (int i = 0; i < 120; i++) {
    SDL_RenderClear(renderer);
    auto&& p = MKStoPixelTransform(car.GetPosition());
    const SDL_Rect where = {
      p.x,    p.y,  // x and y coordinates
      100,    100   // width and height
    };
    SDL_RenderCopy(renderer, texture, NULL, &where);
    SDL_RenderPresent(renderer);

    world.Step(timestep, velocityIterations, positionIterations);
    SDL_Delay(1000 / 60);   // wait 1/60th of a second
    car.GasOn();
  }

	SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
