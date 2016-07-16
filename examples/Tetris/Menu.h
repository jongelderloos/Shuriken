#ifndef MENU_H_
#define MENU_H_

#include "menu.h"
#include "Render2D.h"

typedef enum
{
  MENU_START,
  MENU_HIGHSCORES,
  MENU_QUIT
} MENU_STATE;


class Menu
{

public:
  Menu();
  ~Menu();
  void handleInput(char key);
  void menuSelected();
  int getSelected();
  void menuDown();
  void menuUp();
  void draw();
  void setVideoMemory(void* memory, int width, int height);
  void setRender(Render2D *render);
  void addItems();
  void removeItems();
private:
  bool selected;
  MENU_STATE menuState;
  void* videoMemPtr;
  int windowWidth;
  int windowHeight;
  Render2D *render;
  bool itemsAdded;
};

#endif // MENU_H_
