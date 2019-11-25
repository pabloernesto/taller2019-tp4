#ifndef _AI_H_
#define _AI_H_

#ifdef __cplusplus
  #include <lua5.3/lua.hpp>
#else
  #include <lua.h>
  #include <lualib.h>
  #include <lauxlib.h>
#endif
#include <thread>
#include <atomic>
#include "CarProxy.h"
#include "RaceProxy.h" 

class Ai{
  private:
    static const int SLEEP_TIME_MS;
    // Used pointer because of extern "C"
    CarProxy* car;
    RaceProxy* race;
    lua_State* L;

    std::atomic<bool> quit;
    std::thread thread;

    int decide(int prev_decision);
    void passCurrentPosition();
    void passPrevDecision(int prev_decision);
    void passMap();
    void loadXandYonTable(float x, float y);
    void loadTrackPiece(float x, float y, int type);

  public:
    Ai(CarProxy* car, RaceProxy* race);
    void run();
    
    virtual void Shutdown();
    virtual void Start();
    virtual void Join();
    virtual ~Ai();

};
#endif