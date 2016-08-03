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
  Circle *ballShape = new Circle(40, 200, 5);
  HitBox2D ballHb(ballShape);
  gameBall.init("Game Ball", ballPos, ballVel, ballHb, 5, true, true, false, 0);

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

  gameTable.addObject(&gameBall);
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
    case 0x26:
      if(tableState == TABLE_PLAYING)
      {
        moveP2Paddle(20);
      }
      break;
    case 0x28:
      if(tableState == TABLE_PLAYING)
      {
        moveP2Paddle(-20);
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
  p1Paddle.pos.y += yDist;

  if(p1Paddle.pos.y > (tableHeight - (p1Paddle.height / 2)))
  {
    p1Paddle.pos.y = (tableHeight - (p1Paddle.height / 2));
  }

  if(p1Paddle.pos.y < (p1Paddle.height / 2))
  {
    p1Paddle.pos.y = (p1Paddle.height / 2);
  }
  
  // Update the hit box too
  if(p1Paddle.hitBox.box1 != NULL)
  {
    p1Paddle.hitBox.box1->pos.y = p1Paddle.pos.y;
  }

  if(p1Paddle.hitBox.box2 != NULL)
  {
    p1Paddle.hitBox.box2->pos.y = p1Paddle.pos.y;
  }
  
  PaddleDrawable *paddle = new PaddleDrawable(p1Paddle.pos.x, p1Paddle.pos.y, p1Paddle.width, p1Paddle.height);
  paddle->id = 1;
  paddle->color = 0xFFFFFF;
  render.updateMiddleground(paddle);
}

void Table::moveP2Paddle(float yDist)
{
  p2Paddle.pos.y += yDist;

  if(p2Paddle.pos.y > (tableHeight - (p2Paddle.height / 2)))
  {
    p2Paddle.pos.y = (tableHeight - (p2Paddle.height / 2));
  }

  if(p2Paddle.pos.y < (p2Paddle.height / 2))
  {
    p2Paddle.pos.y = (p2Paddle.height / 2);
  }
  
  // Update the hit box too
  if(p2Paddle.hitBox.box1 != NULL)
  {
    p2Paddle.hitBox.box1->pos.y = p2Paddle.pos.y;
  }

  if(p2Paddle.hitBox.box2 != NULL)
  {
    p2Paddle.hitBox.box2->pos.y = p2Paddle.pos.y;
  }

  PaddleDrawable *paddle2 = new PaddleDrawable(p2Paddle.pos.x, p2Paddle.pos.y, p2Paddle.width, p2Paddle.height);
  paddle2->id = 2;
  paddle2->color = 0xFFFFFF;
  render.updateMiddleground(paddle2);
}
