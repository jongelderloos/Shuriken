#define GLEW_STATIC

// Disable default log creation
#ifndef ELPP_NO_DEFAULT_LOG_FILE
#define ELPP_NO_DEFAULT_LOG_FILE
#endif

#include "engine.h"
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "easylogging++.h"

#define GLFW_INCLUDE_GLU

#ifndef LOGGING
INITIALIZE_EASYLOGGINGPP
#define LOGGING
#endif

GLFWwindow* window;

__declspec(dllexport) Engine::Engine(Game* nGame)
{
  msCurrent = 0;
  msLast = 0;
  msLastDraw = 0;

  // Setup logging
  el::Configurations conf("logging.conf");
  el::Loggers::reconfigureLogger("default", conf);
  el::Loggers::reconfigureAllLoggers(conf);

  LOG(INFO) << "Starting Engine";

  targetFPS = nGame->getDesiredFPS();
  LOG(INFO) << "TargetFPS: " << targetFPS;

  game = nGame;
  msProcessTime = game->getMsProcessTime();
  LOG(INFO) << "ProcessTime: " << *msProcessTime;
}

__declspec(dllexport) bool Engine::run(ENG_MODE mode)
{
  char key = 0x00;

  LOG(INFO) << "Running Engine";

  msStart = timeGetTime();

  LOG(INFO) << "Starting Game, mode: " << mode;
  game->start();
  engineRunning = game->isRunning();

  // Loop until we end the program
  while(engineRunning)
  {
    // TODO re add this once glfw is working
    /*
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
      key = 0x61;
    } 

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
      key = 0x61;
    } 

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
      key = 0x61;
    } 

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
      key = 0x61;
    } 

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
      key = 0x61;
    } 

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      key = 0x61;
    } 
    */

    // TODO: remove the do while
    // Loop until we get a key press
    do
    {
      if( key != 0x00 )
      {
        LOG(TRACE) << "Input: " << (int)key << ", (" << key << ")";
      }
      
      game->handleInput(key);
      engineRunning = game->isRunning();

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
        game->draw();
        msLastDraw = timeGetTime();
      }

      key = 0x00;
    } while(getInput(&key, mode));
  } // Main loop
  return true;
}

__declspec(dllexport) int Engine::init(void)
{
  if(!glfwInit())
  {
    LOG(ERROR) << "Failed to init GLFW";
    return -1;
  }

  return 0;
}

__declspec(dllexport) bool Engine::getInput(char *c, ENG_MODE mode)
{
  if(kbhit())
  {
    *c = _getch();
    if( mode == ENG_NORMAL )
    {
      return true;
    }
    else // Replay mode
    {
      if( *c == 0x1B ) // ESC
      {
        return true;
      }
      else // TODO: Get input from replay file here
      {
        *c = 0x00;
      }
    }
  }

  // TODO need system with opengl
  /*
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, 0);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  window = glfwCreateWindow(800, 600, "Test Window", NULL, NULL);
  if(window == NULL)
  {
    printf("Failed to open GLFW Window\n");
    glfwTerminate();
    return -1;
  }
  */

  return false;
}

