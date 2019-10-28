#ifndef _AI_H_
#define _AI_H_

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
// #include "Map.h"
#include "Point.h"

class Ai{
  private:
    // Map& map;
    Point& point;
    lua_State* L;
    // Aca se cambiaria por auto/modelo.

  private:
    void decideNewPosition();
    void passCurrentPosition();
    void loadPosition(size_t x, size_t y);
    void loadMapPositions();
    void passMap();

  public:
    Ai(/*Map& map,*/ Point& point);
    void run();
    ~Ai();
};

#endif