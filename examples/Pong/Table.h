#ifndef TABLE_H_
#define TABLE_H_

#include "game.h"
#include "ball.h"
#include "paddle.h"
#include "PhysSpace2D.h"

typedef enum
{
  TABLE_START,
  TABLE_PLAYING,
  TABLE_DONE
} TABLE_STATE;

class Table : public Game
{

public:
  Table();
  ~Table();
  void start(void) override;
  void handleInput(char) override;
  void update(void) override;
  int getDesiredFPS(void) override;
  unsigned int* getMsProcessTime(void) override;
  void draw(void) override;

private:
  void moveP1Paddle(float);
  PhysSpace2D gameTable;
  Ball gameBall;
  Paddle p1Paddle;
  Paddle p2Paddle;
  int p1Score;
  int p2Score;
  unsigned int msProcessTime;
  float tableHeight;
  float tableWidth;
  TABLE_STATE tableState;
};

#endif // TABLE_H_
