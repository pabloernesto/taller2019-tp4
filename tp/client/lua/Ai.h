#ifndef _AI_H_
#define _AI_H_

#ifdef __cplusplus
  #include <lua.hpp>
#else
  #include <lua.h>
  #include <lualib.h>
  #include <lauxlib.h>
#endif
#include <thread>
#include <atomic>
// Que uso? 
#include "../CarProxy.h"
#include "../RaceProxy.h" 
// o 
// class CarProxy;
// Esto tambien va a formar parte de la libreria?


class Ai{
  private:
    static const int SLEEP_TIME_MS;
    // Used pointer because of extern "C"
    CarProxy* car;
    RaceProxy* race;
    lua_State* L;

    std::atomic<bool> quit;
    std::thread thread;

    int decide();
    void passCurrentPosition();
    void passMap();
    void loadXandYonTable(float x, float y);
    void loadTrackPiece(float x, float y, int type);

  public:
    Ai(CarProxy* car, RaceProxy* race);
    void run();
    
    // void setCar(CarProxy* car);
    virtual void Shutdown();
    virtual void Start();
    virtual void Join();
    ~Ai();

};
#endif