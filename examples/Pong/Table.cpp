#include "Table.h"
#include "stdio.h"
#include "Windows.h"
#include "Box.h"
#include "Circle.h"
#include <string>
#include "PaddleDrawable.h"

Table::Table()
{
  float paddleWidth = 10;
  float paddleHeight = 40;
  tableHeight = 400;
  tableWidth = 600;

  tableState = TABLE_START;

  gameTable.init(tableHeight, tableWidth);

  Point2D ballPos(40, 200);
  Vec2D ballVel(0, 0);
  Circle ballShape(40, 200, 10);
  HitBox2D ballHb(&ballShape);
  // Create a setup function
  gameBall.init("Game Ball", ballPos, ballVel, ballHb, 10, true, true, false, 0);

  OutputDebugStringA(("Ball: " + gameBall.name).c_str());

  Point2D pos1(10, 200);
  Vec2D vel1(0, 0);
  Box *shape1 = new Box(10, 200, paddleHeight, paddleWidth);
  HitBox2D hb1(shape1);
  p1Paddle.init("Player l Paddle", pos1, vel1, hb1, paddleHeight, paddleWidth, true, true, false, 0);

  Point2D pos2(590, 200);
  Vec2D vel2(0, 0);
  Box *shape2 = new Box(590, 200, paddleHeight, paddleWidth);
  HitBox2D hb2(shape2);
  p2Paddle.init("Player 2 Paddle", pos2, vel2, hb2, paddleHeight, paddleWidth, true, true, false, 0);

  //gameTable.addObject(&gameBall);
  gameTable.addObject(&p1Paddle);
  gameTable.addObject(&p2Paddle);

  p1Score = 0;
  p2Score = 0;

  msProcessTime = 100;

  PaddleDrawable *background = new PaddleDrawable(300, 200, 600, 400);
  background->id = 1000;
  background->color = 0x0;
  render.addToBackground(background);

  PaddleDrawable *paddle = new PaddleDrawable(p1Paddle.pos.x, p1Paddle.pos.y, p1Paddle.width, p1Paddle.height);
  paddle->id = 1;
  paddle->color = 0xFFFFFF;
  render.addToMiddleground(paddle);

  PaddleDrawable *paddle2 = new PaddleDrawable(p2Paddle.pos.x, p2Paddle.pos.y, p2Paddle.width, p2Paddle.height);
  paddle2->id = 2;
  paddle2->color = 0xFFFFFF;
  render.addToMiddleground(paddle2);
}

Table::~Table()
{
}

void Table::setVideoMemory(void* memoryPtr, int width, int height)
{
  render.setWindowSize(width, height);
  render.setScreenBuffer(memoryPtr);
}

void Table::start(void)
{
  Game::start();
}

void Table::handleInput(char key)
{
  switch(key)
  {
    case 0x20: // space
      tableState = TABLE_PLAYING;
      break;
    case 0x53:
    case 0x73: // s
      if(tableState == TABLE_PLAYING)
      {
        moveP1Paddle(-20);
      }
      break;
    case 0x57:
    case 0x77: // w
      if(tableState == TABLE_PLAYING)
      {
        moveP1Paddle(20);
      }
      break;
    default:
      break;
  }
}

void Table::update(void)
{
  if(tableState == TABLE_PLAYING)
  {
    gameTable.tick();
  }
  //cout << gameBall.name << ": pos(" << gameBall.pos.x << "," << gameBall.pos.y << ")";
  //cout << p1Paddle.name << ": pos(" << p1Paddle.pos.x << "," << p1Paddle.pos.y << ")";
  //cout << p2Paddle.name << ": pos(" << p2Paddle.pos.x << "," << p2Paddle.pos.y << ")";
  //OutputDebugStringA((gameBall.name + ": pos(" + gameBall.pos.x + "," + gameBall.pos.y).c_str());
  //OutputDebugStringA((p1Paddle.name + ": pos(" + p1Paddle.pos.x + "," + p1Paddle.pos.y).c_str());
  //OutputDebugStringA((p2Paddle.name + ": pos(" + p2Paddle.pos.x + "," + p2Paddle.pos.y).c_str());
}

int Table::getDesiredFPS(void)
{
  return 60;
}

unsigned int* Table::getMsProcessTime(void)
{
  return &msProcessTime;
}

void Table::draw(void)
{
  render.run();
}

void Table::moveP1Paddle(float yDist)
{
  //cout << "Moving paddle 1: " << yDist;
  //OutputDebugStringA(("Moving paddke 1: " + yDist).c_str());
  p1Paddle.pos.y += yDist;

  //cout << "New Paddle height: " << p1Paddle.pos.x;
  //OutputDebugStringA(("New paddle height: " + p1Paddle.pox.x).c_str());

  if(p1Paddle.pos.y > (tableHeight - (p1Paddle.height / 2)))
  {
    p1Paddle.pos.y = (tableHeight - (p1Paddle.height / 2));
  }

  if(p1Paddle.pos.y < (p1Paddle.height / 2))
  {
    p1Paddle.pos.y = (p1Paddle.height / 2);
  }
  
  //OutputDebugStringA(("New paddle height: " + p1Paddle.pos.x).c_str());
  //cout << "New Paddle height: " << p1Paddle.pos.x;
  PaddleDrawable *paddle = new PaddleDrawable(p1Paddle.pos.x, p1Paddle.pos.y, p1Paddle.width, p1Paddle.height);
  paddle->id = 1;
  paddle->color = 0xFFFFFF;
  render.updateMiddleground(paddle);

  PaddleDrawable *paddle2 = new PaddleDrawable(p2Paddle.pos.x, p2Paddle.pos.y, p2Paddle.width, p2Paddle.height);
  paddle2->id = 2;
  paddle2->color = 0xFFFFFF;
  render.addToMiddleground(paddle2);
}
