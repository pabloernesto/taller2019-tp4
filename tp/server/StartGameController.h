#ifndef _STARTGAMECONTROLLER_H_
#define _STARTGAMECONTROLLER_H_
#include "../common/Responsibility.h"
#include "Game.h"

class StartGameController : public TaskHandler {

  private:
    Game& game;

  public:
    StartGameController(TaskHandler* next, Game& game);
    virtual bool ShouldHandle(void* t) override;
    virtual bool OnHandle(void* t) override;
};


#endif