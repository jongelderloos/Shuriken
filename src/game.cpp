#include "game.h"

__declspec(dllexport) Game::Game()
{
}

__declspec(dllexport) Game::~Game()
{
}

__declspec(dllexport) void Game::start(void)
{
  running = true;
}

__declspec(dllexport) void Game::end(void)
{
  running = false;
}

__declspec(dllexport) bool Game::isRunning(void)
{
  return running;
}

__declspec(dllexport) void Game::handleInput(char key)
{
  // TODO this is just to fix the unused variable error
  // This function should always be overriden by the child class
  key++;
}

__declspec(dllexport) void Game::update(void)
{
}

__declspec(dllexport) void Game::setVideoMemory(void* memoryPtr, int width, int height)
{
  videoMemPtr = memoryPtr;
  windowWidth = width;
  windowHeight = height;
}

__declspec(dllexport) void Game::draw(void)
{
}

__declspec(dllexport) int Game::getDesiredFPS(void)
{
  return 60;
}

__declspec(dllexport) unsigned int* Game::getMsProcessTime(void)
{
  static unsigned int time = 250;
  return &time;
}

