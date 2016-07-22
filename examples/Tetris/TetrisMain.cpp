#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "engine.h"
#include "Tetris.h"

int WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdShow)
{
 
  srand(time(0));

  Tetris tetrisGame;

  Engine myEngine(&tetrisGame, instance, prevInstance, cmdLine, cmdShow, "Tetris", false, 375, 550);
  myEngine.init();

  myEngine.run(ENG_NORMAL);

  return 0;
}

