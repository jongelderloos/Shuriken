#ifndef ENGINE_H_
#define ENGINE_H_

#include "game.h"

typedef enum
{
  ENG_NORMAL,
  ENG_REPLAY
} ENG_MODE;

class __declspec(dllexport) Engine
{

public:
  Engine(Game*);
  bool run(ENG_MODE mode);
  int init(void);
  bool getInput(char *c, ENG_MODE mode);
  
private:
  bool engineRunning;
  unsigned int msStart;
  unsigned int msLast;
  unsigned int msLastDraw;
  unsigned int* msProcessTime;
  unsigned int msCurrent;
  float targetFPS;
  Game* game;
};

#endif // ENGINE_H_
