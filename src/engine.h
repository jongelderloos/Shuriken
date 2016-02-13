#ifndef ENGINE_H_
#define ENGINE_H_

#include "game.h"
#include <windows.h>

typedef enum
{
  ENG_NORMAL,
  ENG_REPLAY
} ENG_MODE;

class __declspec(dllexport) Engine
{

public:
  Engine(Game* nGame, HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int showCode, char* name, bool consoleMode);
  void regularWndProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
  static LRESULT CALLBACK MainWindowCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
  bool run(ENG_MODE mode);
  int init(void);
  bool getInput(char *c, ENG_MODE mode);
  
  bool engineRunning;
  Game* game;
  
private:
  bool createWindow(HINSTANCE Instance, char* name);
  static void resizeDIBSection(int width, int height, Engine* engPtr);
  static void updateWindow(HDC deviceContext, RECT windowREct, int x, int y, int width, int height, Engine* engPtr);

  unsigned int msStart;
  unsigned int msLast;
  unsigned int msLastDraw;
  unsigned int* msProcessTime;
  unsigned int msCurrent;
  float targetFPS;
  HWND window;
  BITMAPINFO bitmapInfo;
  void* bitmapMemory;
  int bitmapWidth;
  int bitmapHeight;
};

#endif // ENGINE_H_
