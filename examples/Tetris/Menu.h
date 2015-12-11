#ifndef MENU_H_
#define MENU_H_

#include "menu.h"

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
private:
  bool selected;
  MENU_STATE menuState;
};

#endif // MENU_H_
