#include "Ai.h"
#include "TrackPieceProxy.h"
#include <chrono>  
#include <iostream>
const int Ai::SLEEP_TIME_MS = 100;

extern "C" Ai* createAi(CarProxy* car, RaceProxy* race){
  return new Ai(car, race);
}

extern "C" void destroyAi(Ai* ai){
  delete ai;
}

// extern "C" { static int printNumber(lua_State* L){
//   double d = lua_tonumber(L, 1);
//   std::cout << "Numero: " << d << '\n';
//   return 0;
// }
// }


Ai::Ai(CarProxy* car, RaceProxy* race) : car(car), race(race), quit(false) {
  this->L = luaL_newstate();
  luaL_openlibs(L);
  int r_v = luaL_dofile(L, "Ai.lua");
  if (r_v != 0){
    std::cout << "Error: " << r_v << '\n';
  }
  // lua_pushcfunction(L, printNumber);
  // lua_setglobal(L, "printnum");
}

void Ai::run(){
  std::cout << "Ai started\n";
  int decision = 0;
  while (!this->quit){
    int decision = this->decide(decision);
    // std::cout << "Track on table: ";
    // luaL_dostring(L, "print(current_track)");
    // std::cout << "Track position_x: ";
    // luaL_dostring(L, "print(map[current_track][1])");
    // std::cout << "Track position_y: ";
    // luaL_dostring(L, "print(map[current_track][2]");
    // luaL_dostring(L, "print(disty)");
    // std::cout << "Car position_x: ";
    // luaL_dostring(L, "print(car[1])");
    // std::cout << "Car position_y: ";
    // luaL_dostring(L, "print(car[2]");
    
    std::cout << "Decision: " << decision << '\n';
    if (decision == 0) {
      car->BreakOff();
      car->SteerCenter();
      car->GasOn();
    }
    else if (decision == 1) car->GasOff();
    else if (decision == 2){
      car->BreakOff();
      car->SteerCenter();
      car->GasOn();
    }  
    else if (decision == 3) {
      car->BreakOff();
      car->SteerRight();
      car->GasOn();
    }
    else if (decision == 4){
      car->BreakOff();
      car->SteerLeft();
      car->GasOn();
    }  
    else if (decision == 5) car->BreakOn(); 
    else if (decision == 6) car->BreakOff();

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME_MS));    
  }
}

int Ai::decide(int prev_decision){
  this->passCurrentPosition();
  this->passPrevDecision(prev_decision);
  this->passMap();
  lua_getglobal(L, "decide");

  // Call the function with zero arguments and expect one result.
  int error = lua_pcall(L, 0, 1, 0);
  if (error != 0){
    std::cout << "Error: " << error << '\n';
    std::cout << lua_tostring(L, -1) << '\n';
  }

  // Get the result number on the top of the stack.
  int result = lua_tonumber(L, -1);
  return result;
}

void Ai::passPrevDecision(int prev_decision){
  lua_pushnumber(this->L, prev_decision);
  lua_setglobal(this->L, "prev_decision");
}

void Ai::passCurrentPosition(){
  std::vector<float> pos = this->car->GetPosition();
  // std::cout << "Car_x: " << pos[0] << " " << pos[1] << '\n';
  this->loadXandYonTable(pos[0], pos[1]);
  // Pop table and save it on global variable "car"
  lua_setglobal(this->L, "car");
}

void Ai::passMap(){
  std::vector<std::unique_ptr<TrackPieceProxy>>& track_pieces = this->race->getTrackPieces();
  
  // Send track_piece_size
  std::vector<float> size = track_pieces.front()->GetSize();
  this->loadXandYonTable(size[0], size[1]);
  // Pop table and save it on global variable "track_size"
  lua_setglobal(this->L, "track_size");

  // Create and push the map table
  lua_newtable(this->L);

  // Fill the table with the positons
  size_t map_table_index = 1;
  for (auto it = track_pieces.begin(); it != track_pieces.end(); it++){
    std::vector<float> pos = (*it)->GetPosition();
    // Push index of the next position (which is a table)
    lua_pushnumber(this->L, map_table_index);
    // Load the position
    this->loadTrackPiece(pos[0], pos[1], (*it)->getTrackType());
    // Set the created position in the pushed index in the map table.
    lua_settable(this->L, -3);
    map_table_index++;  
  }

  // Pop and assign the map table to de global variable.
  lua_setglobal(this->L, "map");
}

void Ai::loadTrackPiece(float x, float y, int type){
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
  
  lua_pushnumber(this->L, 3);
  lua_pushnumber(this->L, type);
  lua_settable(this->L, -3); //-3 because it's the table pos in the stack

  // Now i have a loaded table in the stack
}

void Ai::loadXandYonTable(float x, float y){
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

// Thread methods
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