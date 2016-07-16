#include "Menu.h"
#include "stdio.h"
#include "Windows.h"
#include "TextDrawable.h"

HANDLE menuOutput;
COORD menuPos;

MENU_STATE menuState;


Menu::Menu()
{
  menuState = MENU_START;
  selected = false;
  menuOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  itemsAdded = false;
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
    case 0x53:
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

void Menu::setVideoMemory(void* memory, int width, int height)
{
  videoMemPtr = memory;
  windowWidth = width;
  windowHeight = height;
}

void Menu::setRender(Render2D *render)
{
  this->render = render;
}

void Menu::addItems()
{
  if(!itemsAdded)
  {
    TextDrawable *startText = new TextDrawable("START", 26, 70, true);
    startText->id = 8001;
    startText->SetSize(2);
    render->addToForeground(startText);

    TextDrawable *highscoresText = new TextDrawable("HIGHSCORES", 19, 60, true);
    highscoresText->id = 8002;
    highscoresText->SetSize(2);
    render->addToForeground(highscoresText);

    TextDrawable *quitText = new TextDrawable("QUIT", 26, 50, true);
    quitText->id = 8003;
    quitText->SetSize(2);
    render->addToForeground(quitText);

    itemsAdded = true;
  }
}

void Menu::removeItems()
{
  render->removeForeground(8001);
  render->removeForeground(8002);
  render->removeForeground(8003);

  itemsAdded = false;
}

void Menu::draw(void)
{
  if( menuState == MENU_START )
  {
    TextDrawable *startText = new TextDrawable("START", 26, 70, true);
    startText->id = 8001;
    startText->SetColor(0xFF0000);
    startText->SetSize(2);
    render->updateForeground(startText);
  }
  else
  {
    TextDrawable *startText = new TextDrawable("START", 26, 70, true);
    startText->id = 8001;
    startText->SetSize(2);
    render->updateForeground(startText);
  }

  if( menuState == MENU_HIGHSCORES )
  {
    TextDrawable *highscoresText = new TextDrawable("HIGHSCORES", 19, 60, true);
    highscoresText->id = 8002;
    highscoresText->SetColor(0xFF0000);
    highscoresText->SetSize(2);
    render->updateForeground(highscoresText);
  }
  else
  {
    TextDrawable *highscoresText = new TextDrawable("HIGHSCORES", 19, 60, true);
    highscoresText->id = 8002;
    highscoresText->SetSize(2);
    render->updateForeground(highscoresText);
  }

  if( menuState == MENU_QUIT )
  {
    TextDrawable *quitText = new TextDrawable("QUIT", 26, 50, true);
    quitText->id = 8003;
    quitText->SetColor(0xFF0000);
    quitText->SetSize(2);
    render->updateForeground(quitText);
  }
  else
  {
    TextDrawable *quitText = new TextDrawable("QUIT", 26, 50, true);
    quitText->id = 8003;
    quitText->SetSize(2);
    render->updateForeground(quitText);
  }

  render->run();
}

