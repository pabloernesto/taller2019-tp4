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
// o 
// class CarProxy;
// Esto tambien va a formar parte de la libreria?


class Ai{
  private:
    static const int SLEEP_TIME_MS;
    // Used pointer because of extern "C"
    CarProxy* car;
    lua_State* L;

    std::atomic<bool> quit;
    std::thread thread;

    int decide();

  public:
    Ai(CarProxy* car);
    void run();
    
    // void setCar(CarProxy* car);
    void Shutdown();
    void Start();
    void Join();
    ~Ai();

};
#endif