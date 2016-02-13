#include "Menu.h"
#include "stdio.h"
#include "Windows.h"

HANDLE menuOutput;
COORD menuPos;

MENU_STATE menuState;


Menu::Menu()
{
  menuState = MENU_START;
  selected = false;
  menuOutput = GetStdHandle(STD_OUTPUT_HANDLE);
}

Menu::~Menu()
{
}

void Menu::handleInput(char key)
{
  switch(key)
  {
    case 0x77:
    case 0x57:
      menuUp();
      break;
    case 0x73:
    case 0x52:
      menuDown();
      break;
    case 0x0D:
      menuSelected();
      break;
    case 0x1B:
      menuState = MENU_QUIT;
      selected = true;
    default:
      break;
  }
}

void Menu::menuSelected()
{
  selected = true;
}

int Menu::getSelected()
{
  if( selected == true )
  {
    selected = false;
    return (int)menuState;
  }
  else
  {
    return -1;
  }
}

void Menu::menuDown()
{
  int menuNum = (int)menuState;
  menuNum = menuNum + 1;

  if( menuNum > (int)MENU_QUIT )
  {
    menuNum = 0;
  }

  menuState = (MENU_STATE)menuNum;
}

void Menu::menuUp()
{
  int menuNum = (int)menuState;
  menuNum = menuNum - 1;

  if( menuNum < (int)MENU_START )
  {
    menuNum = 2;
  }

  menuState = (MENU_STATE)menuNum;
}

void Menu::draw(void)
{
  //system("CLS");

  //menuPos.X = 0;
  //menuPos.Y = 0;
  //SetConsoleCursorPosition(menuOutput, menuPos);
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("*                     *\n");
  //printf("***********************\n");

  //menuPos.X = 6;
  //menuPos.Y = 6;
  //SetConsoleCursorPosition(menuOutput, menuPos);
  if( menuState == MENU_START )
  {
    //SetConsoleTextAttribute(menuOutput, BACKGROUND_GREEN);
  }
  else
  {
    //SetConsoleTextAttribute(menuOutput, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN );
  }
  //printf("New Game");

  //menuPos.X = 6;
  //menuPos.Y = 8;
  //SetConsoleCursorPosition(menuOutput, menuPos);
  if( menuState == MENU_HIGHSCORES )
  {
    //SetConsoleTextAttribute(menuOutput, BACKGROUND_GREEN);
  }
  else
  {
    //SetConsoleTextAttribute(menuOutput, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN );
  }
  //printf("High Scores");

  //menuPos.X = 6;
  //menuPos.Y = 10;
  //SetConsoleCursorPosition(menuOutput, menuPos);
  if( menuState == MENU_QUIT )
  {
    //SetConsoleTextAttribute(menuOutput, BACKGROUND_GREEN);
  }
  else
  {
    //SetConsoleTextAttribute(menuOutput, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN );
  }
  //printf("Exit");

  //SetConsoleTextAttribute(menuOutput, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN );
}

