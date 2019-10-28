#include "ai.h"

#ifdef __cplusplus
  #include <lua.hpp>
#else
  #include <lua.h>
  #include <lualib.h>
  #include <lauxlib.h>
#endif
// extern "C"{
//     #include <lualib.h>
//     #include <lauxlib.h>
//     #include <lua.h>
// }
#define file_path "ai.lua"
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>


Ai::Ai(/*Map& map,*/ Point& point) : point(point){
  this->L = luaL_newstate();
  luaL_openlibs(L);
  luaL_dofile(L, "ai.lua");
  // Hay que verificar este resultado...
}

void Ai::run(){

  for (size_t i = 0; i < 50; i++){
    std::vector<int> pos;
    std::cout << "Current positions:\n";
     pos = this->point.getPosition();
    // std::vector<std::vector<int>> pos = map.getPositions();
    std::cout << "(" << pos[0] << ", ";
    std::cout << pos[1] << ")" << "\n";
    this->decideNewPosition();
    pos = this->point.getPosition();
    std::cout << "LUA's new positions:\n";
    std::cout << "(" << pos[0] << ", ";
    std::cout << pos[1] << ")" << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void Ai::decideNewPosition(){
  this->passCurrentPosition();
  // this->passMap();

  lua_getglobal(L, "decide");
  // Creo que podria hacer este getglobal antes y despues cargar todo lo demas
  // para hacer el call de la funcion despues.
  
  // Call the function with zero arguments and expect one result.
  lua_pcall(L, 0, 1, 0);
  // Get the result number on the top of the stack.
  int result = lua_tonumber(L, -1);
  if (result == 0){
    this->point.moveRight();
  }
}

void Ai::passCurrentPosition(){
  std::vector<int> pos = this->point.getPosition();
  this->loadPosition(pos[0], pos[1]);
  // Pop table and save it on global variable "position"
  lua_setglobal(this->L, "position");
} 

/*
void Ai::passMap(){
  // Create and push the map table
  lua_newtable(this->L);
  // Fill the table with the positons
  this->loadMapPositions();
  // Pop and assign the map table to de global variable.
  lua_setglobal(this->L, "map");
}


void Ai::loadMapPositions(){
  std::vector<std::vector<int>> pos = this->map.getPositions();
  size_t table_index = 1;
  for (auto it = pos.begin(); it != pos.end(); it++){
    // Push index of the next position (which is a table)
    lua_pushnumber(this->L, table_index);
    // Create and leave pushed next position
    this->loadPosition((*it)[0], (*it)[1]);
    // Set the created position in the pushed index in the map table.
    lua_settable(this->L, -3);
    table_index++;
  }
}*/

void Ai::loadPosition(size_t x, size_t y){
  // Create new table and push it into the stack
  lua_newtable(this->L);
  // Push x in index = 1 (of table)
  lua_pushnumber(this->L, 1);
  lua_pushnumber(this->L, x);
  // Set the coordenate in the pushed index in the position table
  lua_settable(this->L, -3); //-3 because it's the table pos in the stack
  // Push y in index = 2 (of table)
  lua_pushnumber(this->L, 2);
  lua_pushnumber(this->L, y);
  // Set the coordenate in the pushed index in the position table
  lua_settable(this->L, -3); //-3 because it's the table pos in the stack
  // Now i have a loaded table in the stack  
}

Ai::~Ai(){
  lua_close(L);
}