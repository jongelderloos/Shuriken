#include "Tetris.h"
#include "stdio.h"
#include "Windows.h"

Tetris::Tetris()
{
  appState = APP_MENU;
}

Tetris::~Tetris()
{
}

void Tetris::start(void)
{
  Game::start();
 
  // TODO: set back to menu once we have graphics
  //appState = APP_MENU;
  appState = APP_RUNNING;
  msProcessTime = 250;
}

void Tetris::handleInput(char key)
{
  if(appState == APP_MENU)
  {
    mainMenu.handleInput(key);
  }
  
  if(appState == APP_RUNNING)
  {
    gameBoard.handleInput(key);
  }
}

void Tetris::update(void)
{
  if(appState == APP_MENU)
  {
    int ret;
    ret = mainMenu.getSelected();
    
    if(ret == 0)
    {
      appState = APP_RUNNING;
      gameBoard.start();
    }
    
    if(ret == 1)
    {
      appState = APP_MENU;
      //appState = APP_HIGHSCORES;
    }
    
    if(ret == 2)
    {
        appState = APP_END;
        Game::end();
    }
  }
    
  if(appState == APP_RUNNING)
  {
    gameBoard.update();
    
    if(gameBoard.isRunning() == false)
    {
      OutputDebugStringA("Game stoped runnung");
      // TODO: set back to menu once we have graphics
      //appState = APP_MENU;
      appState = APP_RUNNING;
    }
  }
}

int Tetris::getDesiredFPS(void)
{
  return 60;
}

unsigned int* Tetris::getMsProcessTime(void)
{
  return gameBoard.getMsProcessTime();
}

void Tetris::setVideoMemory(void* memoryPtr, int width, int height)
{
  gameBoard.setVideoMemory(memoryPtr, width, height);
}

void Tetris::draw(void)
{
  if(appState == APP_MENU)
  {
    mainMenu.draw();
  }

  if(appState == APP_RUNNING)
  {
    gameBoard.draw();
  }
}
