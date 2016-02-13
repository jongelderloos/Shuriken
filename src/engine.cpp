#include "engine.h"
#include "stdio.h"
#include "stdint.h"
#include <xinput.h>

__declspec(dllexport) Engine::Engine(Game* nGame, HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine,
                                     int showCode, char* name, bool consoleMode)
{
  char msgBuf[256] = {0};
  msCurrent = 0;
  msLast = 0;
  msLastDraw = 0;

  if(!consoleMode)
  {
    if(!this->createWindow(instance, name))
    {
      OutputDebugStringA("Failed to create window");
    }
  }

  targetFPS = nGame->getDesiredFPS();
 
  sprintf(msgBuf, "TargetFPS: %f", targetFPS);
  OutputDebugStringA(msgBuf);

  game = nGame;
  msProcessTime = game->getMsProcessTime();
  
  sprintf(msgBuf, "ProcessTime: %d", *msProcessTime);
  OutputDebugStringA(msgBuf);
}

bool Engine::createWindow(HINSTANCE instance, char* name)
{
  bool success = false;
  WNDCLASSA windowClass = {0};
  HDC deviceContext;

  resizeDIBSection(1024, 768, this);

  // Make it so the entire window is resized on these events
  windowClass.style = CS_HREDRAW|CS_VREDRAW;

  windowClass.lpfnWndProc = &Engine::MainWindowCallback;
  windowClass.hInstance = instance;
  windowClass.lpszClassName = name;

  if(RegisterClassA(&windowClass))
  {
    window = CreateWindowExA(0, windowClass.lpszClassName, windowClass.lpszClassName, WS_OVERLAPPEDWINDOW|WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, instance, this);

    if(window)
    {
      deviceContext = GetDC(window);
      if(deviceContext)
      {
        success = true;
        ReleaseDC(window, deviceContext);
      }
    }
  }

  return success;
}

__declspec(dllexport) bool Engine::run(ENG_MODE mode)
{
  char msgBuf[256] = {0};

  OutputDebugStringA("Running Engine");

  msStart = timeGetTime();

  sprintf(msgBuf, "Starting Game, mode: %d", mode);
  OutputDebugStringA(msgBuf);

  game->start();
  game->setVideoMemory(bitmapMemory, bitmapWidth, bitmapHeight);
  engineRunning = game->isRunning();

  // Loop until we end the program
  while(engineRunning)
  {
    // Update isRunning from the game
    engineRunning = game->isRunning();

    // Process messages for our window
    MSG message;
    while(PeekMessage(&message, 0, 0, 0, PM_REMOVE))
    {
      if(message.message == WM_QUIT)
      {
        engineRunning = false;
      }
      TranslateMessage(&message);
      DispatchMessageA(&message);
    }

    msCurrent = timeGetTime();

    // Process game logic
    if((msCurrent - msLast) > *msProcessTime)
    {
      game->update();
      msLast = msCurrent;
    }

    msCurrent = timeGetTime();

    // Render
    if((msCurrent - msLastDraw) > (1000 / targetFPS))
    {
      // render to memory
      game->draw();

      // update window
      HDC deviceContext = GetDC(window);
      RECT clientRect;
      GetClientRect(window, &clientRect);
      int windowWidth = clientRect.right - clientRect.left;
      int windowHeight = clientRect.bottom - clientRect.top;
      updateWindow(deviceContext, clientRect, 0, 0, windowWidth, windowHeight, this);
      ReleaseDC(window, deviceContext);
      msLastDraw = timeGetTime();
    }
  } // Main loop
  return true;
}

void Engine::resizeDIBSection(int width, int height, Engine* engPtr)
{
  // TODO: dont free first, free after, then free first if that fails
  if(engPtr->bitmapMemory)
  {
    VirtualFree(engPtr->bitmapMemory, 0, MEM_RELEASE);
  }

  engPtr->bitmapWidth = width;
  engPtr->bitmapHeight = height;

  engPtr->bitmapInfo.bmiHeader.biSize = sizeof(engPtr->bitmapInfo.bmiHeader);
  engPtr->bitmapInfo.bmiHeader.biWidth = engPtr->bitmapWidth;
  engPtr->bitmapInfo.bmiHeader.biHeight = engPtr->bitmapHeight;
  engPtr->bitmapInfo.bmiHeader.biPlanes = 1;
  engPtr->bitmapInfo.bmiHeader.biBitCount = 32;
  engPtr->bitmapInfo.bmiHeader.biCompression = BI_RGB;

  int bytesPerPixel = 4;
  engPtr->bitmapMemory = VirtualAlloc(0, (bytesPerPixel * engPtr->bitmapWidth * engPtr->bitmapHeight), MEM_COMMIT, PAGE_READWRITE);
  // Update the video memory ptr stored by the game
}

void Engine::updateWindow(HDC deviceContext, RECT windowRect, int x, int y, int width, int height, Engine* engPtr)
{
  int windowWidth = windowRect.right - windowRect.left;
  int windowHeight = windowRect.bottom - windowRect.top;
  StretchDIBits(deviceContext, 0, 0, windowWidth, windowHeight, 0, 0, engPtr->bitmapWidth, engPtr->bitmapHeight, 
      engPtr->bitmapMemory, &engPtr->bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}

LRESULT CALLBACK Engine::MainWindowCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
  Engine* engPtr;
  LRESULT result = 0;

  // Handle the case where this is called prior to WM_NCCREATE
  if(LONG_PTR userData = GetWindowLongPtr(window, GWLP_USERDATA))
  {
    engPtr = reinterpret_cast<Engine*>(userData);
  }

  switch(message)
  {
    // On window create get a pointer to the engine
    case WM_NCCREATE:
    {
      OutputDebugStringA("WM_NCCREATE");
      LPCREATESTRUCT createStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
      void* lpCreateParam = createStruct->lpCreateParams;
      engPtr = reinterpret_cast<Engine*>(lpCreateParam);

      if(!SetWindowLongPtr(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(engPtr)))
      {
        if(GetLastError() != 0)
        {
          return FALSE;
        }
      }
      return DefWindowProc(window, message, wParam, lParam);

    } break;

    case WM_SIZE:
    {
      OutputDebugStringA("WM_SIZE");
      engPtr = reinterpret_cast<Engine*>(GetWindowLongPtr(window, GWLP_USERDATA));
      RECT clientRect;
      GetClientRect(window, &clientRect);
      int width = clientRect.right - clientRect.left;
      int height = clientRect.bottom - clientRect.top;
      engPtr->resizeDIBSection(width, height, engPtr);
    } break;

    case WM_CLOSE:
    {
      OutputDebugStringA("WM_CLOSE");
      engPtr = reinterpret_cast<Engine*>(GetWindowLongPtr(window, GWLP_USERDATA));
      if(engPtr)
      {
        engPtr->engineRunning = false;
      }
    } break;

    case WM_ACTIVATEAPP:
    {
      OutputDebugStringA("WM_ACTIVATEAPP");
    } break;

    case WM_DESTROY:
    {
      OutputDebugStringA("WM_DESTROY");
      engPtr = reinterpret_cast<Engine*>(GetWindowLongPtr(window, GWLP_USERDATA));
      if(engPtr)
      {
        engPtr->engineRunning = false;
      }
    } break;

    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    case WM_KEYDOWN:
    case WM_KEYUP:
    {
      unsigned int vkCode = wParam;
      bool wasDown = ((lParam & (1 << 30)) != 0);
      bool isDown = ((lParam & (1 << 31)) == 0);
      // TODO: could add a check for these being opposite
      if(isDown)
      {
        engPtr = reinterpret_cast<Engine*>(GetWindowLongPtr(window, GWLP_USERDATA));
        if(engPtr)
        {
          engPtr->game->handleInput((char)vkCode);
        }
      }
    } break;

    case WM_PAINT:
    {
      OutputDebugStringA("WM_PAINT");
      engPtr = reinterpret_cast<Engine*>(GetWindowLongPtr(window, GWLP_USERDATA));
      PAINTSTRUCT paint;
      HDC deviceContext = BeginPaint(window, &paint);
      int x = paint.rcPaint.left;
      int y = paint.rcPaint.top;
      int width = paint.rcPaint.right = x;
      int height = paint.rcPaint.bottom - y;

      RECT clientRect;
      GetClientRect(window, &clientRect);

      updateWindow(deviceContext, clientRect, x, y, width, height, engPtr);//lParam);
    } break;

    default:
    {
      result = DefWindowProc(window, message, wParam, lParam);
    } break;
  }

  return result;
}
  
__declspec(dllexport) int Engine::init(void)
{
  return 0;
}

