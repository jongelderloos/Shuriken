#include "Table.h"
#include "stdio.h"
#include "Windows.h"
#include "Box.h"
#include "Circle.h"
#include "easylogging++.h"

Table::Table()
{
  float paddleWidth = 10;
  float paddleHeight = 40;
  tableHeight = 400;
  tableWidth = 600;

  tableState = TABLE_START;

  gameTable.init(tableHeight, tableWidth);

  Point2D ballPos(20, 200);
  Vec2D ballVel(0, 0);
  Circle ballShape(20, 200, 10);
  HitBox2D ballHb(ballShape);
  // Create a setup function
  gameBall.init("Game Ball", ballPos, ballVel, ballHb, 10, true, true, false, 0);
  cout << "Ball: " << gameBall.name;

  Point2D pos1(10, 200);
  Vec2D vel1(0, 0);
  Box shape1(10, 200, paddleHeight, paddleWidth);
  HitBox2D hb1(shape1);
  p1Paddle.init("Player 1 Paddle", pos1, vel1, hb1, paddleHeight, paddleWidth, true, true, false, 0);

  Point2D pos2(390, 200);
  Vec2D vel2(0, 0);
  Box shape2(390, 200, paddleHeight, paddleWidth);
  HitBox2D hb2(shape2);
  p2Paddle.init("Player 2 Paddle", pos2, vel2, hb2, paddleHeight, paddleWidth, true, true, false, 0);

  gameTable.addObject(&gameBall);
  gameTable.addObject(&p1Paddle);
  gameTable.addObject(&p2Paddle);

  p1Score = 0;
  p2Score = 0;

  msProcessTime = 100;
}

Table::~Table()
{
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
    case 0x73: // s
      moveP1Paddle(-20);
      break;
    case 0x77: // w
      moveP1Paddle(20);
      break;
    default:
      break;
  }
}

void Table::update(void)
{
  if(tableState == TABLE_PLAYING)
  {
    //gameTable.tick();
  }
  cout << gameBall.name << ": pos(" << gameBall.pos.x << "," << gameBall.pos.y << ")";
  cout << p1Paddle.name << ": pos(" << p1Paddle.pos.x << "," << p1Paddle.pos.y << ")";
  cout << p2Paddle.name << ": pos(" << p2Paddle.pos.x << "," << p2Paddle.pos.y << ")";
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
}

void Table::moveP1Paddle(float yDist)
{
  cout << "Moving paddle 1: " << yDist;
  p1Paddle.pos.x += yDist;

  cout << "New Paddle height: " << p1Paddle.pos.x;

  if(p1Paddle.pos.x > (tableHeight - (p1Paddle.height / 2)))
  {
    p1Paddle.pos.x = (tableHeight - (p1Paddle.height / 2));
  }

  if(p1Paddle.pos.x < (p1Paddle.height / 2))
  {
    p1Paddle.pos.x = (p1Paddle.height / 2);
  }
  
  cout << "New Paddle height: " << p1Paddle.pos.x;
}
