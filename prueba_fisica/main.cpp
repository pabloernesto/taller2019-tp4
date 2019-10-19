#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include <memory>     // unique_ptr
#include <iostream>   // cout
#include "Car.h"

const float32 timestep = 1 / 60.0;
const int32 velocityIterations = 8;
const int32 positionIterations = 3;

int main(int argc, char **argv) {
  SDL_Init(SDL_INIT_EVERYTHING);

  // Create a Window in the middle of the screen
  SDL_Window *window = SDL_CreateWindow(
    "Prueba auto",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // x and y
    640, 480,                                       // Width and Height
    SDL_WINDOW_SHOWN);

  // Setup physics
  b2Vec2 gravity(0, 0);
  b2World world(gravity);

  Car car;
  car.Place(world, (b2Vec2){0, 0});
  car.GasOn();

  // Simulation loop
  for (int i = 0; i < 5; i++) {
    auto position = car.GetPosition();
    std::cout
      << "step " << i << ":    "
      << "x = " << position.x << "  y = " << position.y << "\n";

    world.Step(timestep, velocityIterations, positionIterations);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
}
