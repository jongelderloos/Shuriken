#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "engine.h"
#include "Table.h"

using namespace std;


//int main(int argc, char **argv)
int WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdShow)
{
  srand(time(0));

  Table gameTable;
  
  Engine myEngine(&gameTable, instance, prevInstance, cmdLine, cmdShow, "Pong", false, 600, 400);
  myEngine.init();

  myEngine.run(ENG_NORMAL);
  
  //glfwTerminate();

  return 0;
}

