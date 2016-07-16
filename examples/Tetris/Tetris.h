#ifndef TETRIS_H_
#define TETRIS_H_

#include "menu.h"
#include "board.h"
#include "game.h"

typedef enum
{
  APP_MENU,
  APP_HIGHSCORES,
  APP_RUNNING,
  APP_END
} APP_STATE;

class Tetris : public Game
{

public:
  Tetris();
  ~Tetris();
  void start(void) override;
  void handleInput(char) override;
  void update(void) override;
  void setVideoMemory(void*, int, int) override;
  void draw(void) override;
  int getDesiredFPS(void) override;
  unsigned int* getMsProcessTime(void) override;

private:
  Menu mainMenu;
  Board gameBoard;
  APP_STATE appState;
  unsigned int msProcessTime;
  Render2D render;
};

#endif // TETRIS_H_
