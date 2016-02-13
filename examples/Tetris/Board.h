#ifndef BOARD_H_
#define BOARD_H_

#include "Block.h"
#include <vector>

#define MAX_WIDTH  8
#define MAX_HEIGHT 24

extern struct Falling
{
  int coords[8];
  bool active;
  BLOCK_TYPE type;
  STATE_TYPE state;
} Falling;

typedef enum
{
  STATE_NONE,
  STATE_NORMAL,
  STATE_FLASH,
  STATE_FALLING,
  STATE_DELETE
} ROW_STATE;

typedef enum
{
  MOVE_LEFT,
  MOVE_RIGHT
} MOVE_DIR;

typedef enum
{
  GAME_MENU,
  GAME_RUNNING,
  GAME_PAUSE,
  GAME_END
} GAME_STATE;

class Board
{

public:
  Board();
  ~Board();
  void initializeBoard(void);
  void clearBoard(void);
  Block* getBlock(int, int);
  ROW_STATE getRowState(int);
  void start(void);
  bool isRunning(void);
  void handleInput(char);
  void update(void);
  void setVideoMemory(void*, int, int);
  void draw(void);
  int getDesiredFPS(void);
  unsigned int* getMsProcessTime(void);
  void removeRows(int);
  int addRow(void);
  void evalBoard(void);
  void processBoard(void);
  void drawBoard(void);
  void renderBlock(int, int, uint32_t);
  ROW_STATE getRowState(std::vector<Block*>);
  int getRowsMade(void);
  void addBlock(void);
  void drop(void);
  void moveBlock(MOVE_DIR);
  void rotateClock(void);
  void rotateCounterClock(void);
  struct Falling getFalling(void);
  void setFalling(struct Falling);

private:
  int width;
  int height;
  std::vector<ROW_STATE> rowState;
  std::vector<std::vector<Block*>> board;
  Block blockOnDeck;
  struct Falling fall;
  unsigned int msProcessTime;
  bool running;
  GAME_STATE gameState;
  void* videoMemPtr;
  int windowWidth;
  int windowHeight;
};

#endif // BOARD_H_
