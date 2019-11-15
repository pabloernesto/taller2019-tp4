#include "Ai.h"
#include <chrono>  
const int Ai::SLEEP_TIME_MS = 100;

extern "C" Ai* createAi(CarProxy* car){
  return new Ai(car);
}

extern "C" void destroyAi(Ai* ai){
  delete ai;
}

Ai::Ai(CarProxy* car) : car(car) {
  this->L = luaL_newstate();
  luaL_openlibs(L);
  luaL_dofile(L, "ai.lua");
}

void Ai::run(){
  while (!this->quit){
    int decision = this->decide();
    
    if (decision == 0) car->GasOn();
    else if (decision == 1) car->GasOff();
    else if (decision == 2) car->SteerCenter(); 
    else if (decision == 3) car->SteerRight();
    else if (decision == 4) car->SteerLeft();
    else if (decision == 5) car->BreakOn(); 
    else if (decision == 6) car->BreakOff();

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME_MS));    
  }
}

int Ai::decide(){
  lua_getglobal(L, "decide");

  // Call the function with zero arguments and expect one result.
  lua_pcall(L, 0, 1, 0);

  // Get the result number on the top of the stack.
  int result = lua_tonumber(L, -1);
  return result;
}

void Ai::Shutdown(){
  this->quit = true;
}

void Ai::Start(){
  thread = std::thread(&Ai::run, this);
}

void Ai::Join(){
  if (this->thread.joinable())
    this->thread.join();
}

Ai::~Ai(){
  lua_close(L);
}