#include "Table.h"
#include "stdio.h"
#include "Windows.h"
#include "Box.h"
#include "Circle.h"
#include <string>
#include "PaddleDrawable.h"
#include "CircleDrawable.h"
#include "TextDrawable.h"

//TODO: Add reset and Menu options
//TODO: TextDrawable takes x and y as percent while others are coordinate values
//TODO: Make render know about pixelsPerUnit so I dont have to pass it all the time
//TODO: Move paddleDrawable to box drawable...

Table::Table()
{
  paddleWidth = 1.0f;
  paddleHeight = 4.0f;
  tableHeight = 40.0f;
  tableWidth = 60.0f;
  ballRadius = 0.5;
  pixelsPerUnit = 10.0f;
  wallWidth = 1.0f;

  tableState = TABLE_START;

  // Create the physics world
  b2Vec2 gravity(0.0f, 0.0f);
  worldPtr = new b2World(gravity);

  // Create the bottom wall
  b2BodyDef bottomBodyDef;
  bottomBodyDef.position.Set(30.0f, 0.2F);
  bottomBody = worldPtr->CreateBody(&bottomBodyDef);
  b2PolygonShape bottomBox;
  bottomBox.SetAsBox(tableWidth / 2.0f, wallWidth / 2.0f);
  bottomBody->CreateFixture(&bottomBox, 0.0f);

  // Create the top wall
  b2BodyDef topBodyDef;
  topBodyDef.position.Set(30.0f, 40.0F);
  topBody = worldPtr->CreateBody(&topBodyDef);
  b2PolygonShape topBox;
  topBox.SetAsBox(tableWidth / 2.0f, wallWidth / 2.0f);
  topBody->CreateFixture(&topBox, 0.0f);

  // Create the p1 paddle 
  b2BodyDef p1PaddleBodyDef;
  p1PaddleBodyDef.position.Set(1.0f, 20.0F);
  p1PaddleBody = worldPtr->CreateBody(&p1PaddleBodyDef);
  b2PolygonShape p1PaddleBox;
  p1PaddleBox.SetAsBox(paddleWidth / 2.0f, paddleHeight / 2.0f);
  p1PaddleBody->CreateFixture(&p1PaddleBox, 0.0f);

  // Create the p2 paddle 
  b2BodyDef p2PaddleBodyDef;
  p2PaddleBodyDef.type = b2_staticBody;
  p2PaddleBodyDef.position.Set(59.0f, 20.0F);
  p2PaddleBody = worldPtr->CreateBody(&p2PaddleBodyDef);
  b2PolygonShape p2PaddleBox;
  p2PaddleBox.SetAsBox(paddleWidth / 2.0f, paddleHeight / 2.0);
  p2PaddleBody->CreateFixture(&p2PaddleBox, 0.0f);

  // Create the ball
  b2BodyDef ballBodyDef;
  ballBodyDef.type = b2_dynamicBody;
  ballBodyDef.position.Set(3.0f, 20.0F);
  ballBody = worldPtr->CreateBody(&ballBodyDef);
  b2CircleShape ballShape;
  ballShape.m_p.Set(0.0f, 0.0f);
  ballShape.m_radius = ballRadius;
  b2FixtureDef ballFixtureDef;
  ballFixtureDef.shape = &ballShape;
  ballFixtureDef.density = 1.0f;
  ballFixtureDef.friction = 0.3f;
  ballFixtureDef.restitution = 1.0f;
  ballBody->CreateFixture(&ballFixtureDef);
  ballBody->SetLinearVelocity(b2Vec2(15.0f, 2.0f));

  p1Score = 0;
  p2Score = 0;

  msProcessTime = (1.0f / 60.0f) * 1000.0f;

  PaddleDrawable *background = new PaddleDrawable((tableWidth / 2) * pixelsPerUnit, (tableHeight / 2) * pixelsPerUnit, tableWidth * pixelsPerUnit, tableHeight * pixelsPerUnit);
  background->id = 1000;
  background->color = 0x0;
  render.addToBackground(background);

  b2Vec2 p1PaddlePos = p1PaddleBody->GetPosition();
  PaddleDrawable *paddle = new PaddleDrawable(p1PaddlePos.x * pixelsPerUnit, p1PaddlePos.y * pixelsPerUnit, paddleWidth * pixelsPerUnit, paddleHeight * pixelsPerUnit);
  paddle->id = 1;
  paddle->color = 0xFFFFFF;
  render.addToMiddleground(paddle);

  b2Vec2 p2PaddlePos = p2PaddleBody->GetPosition();
  PaddleDrawable *paddle2 = new PaddleDrawable(p2PaddlePos.x * pixelsPerUnit, p2PaddlePos.y * pixelsPerUnit, paddleWidth * pixelsPerUnit, paddleHeight * pixelsPerUnit);
  paddle2->id = 2;
  paddle2->color = 0xFFFFFF;
  render.addToMiddleground(paddle2);

  b2Vec2 ballPos = ballBody->GetPosition();
  CircleDrawable *circle = new CircleDrawable(ballPos.x * pixelsPerUnit, ballPos.y * pixelsPerUnit, ballRadius * pixelsPerUnit);
  circle->id = 3;
  circle->color = 0xFFFFFF;
  render.addToMiddleground(circle);

  b2Vec2 topWallPos = topBody->GetPosition();
  PaddleDrawable *top = new PaddleDrawable(topWallPos.x * pixelsPerUnit, topWallPos.y * pixelsPerUnit, tableWidth * pixelsPerUnit, wallWidth * pixelsPerUnit);
  top->id = 4;
  top->color = 0xFFFFFF;
  render.addToMiddleground(top);

  b2Vec2 botWallPos = bottomBody->GetPosition();
  PaddleDrawable *bot = new PaddleDrawable(botWallPos.x * pixelsPerUnit, botWallPos.y * pixelsPerUnit, tableWidth * pixelsPerUnit, wallWidth * pixelsPerUnit);
  bot->id = 5;
  bot->color = 0xFFFFFF;
  render.addToMiddleground(bot);

  char p1ScoreString[20];
  sprintf(p1ScoreString, "%d", p1Score);
  TextDrawable *p1ScoreText = new TextDrawable(p1ScoreString, 30.0f, 90.0f, false);
  p1ScoreText->id = 2000;
  p1ScoreText->SetColor(0xFFFFFF);
  p1ScoreText->SetSize(3);
  render.addToForeground(p1ScoreText);

  char p2ScoreString[20];
  sprintf(p2ScoreString, "%d", p2Score);
  TextDrawable *p2ScoreText = new TextDrawable(p2ScoreString, 70.0f, 90.0f, false);
  p2ScoreText->id = 2000;
  p2ScoreText->SetColor(0xFFFFFF);
  p2ScoreText->SetSize(3);
  render.addToForeground(p2ScoreText);
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
        moveP1Paddle(-2);
      }
      break;
    case 0x57:
    case 0x77: // w
      if(tableState == TABLE_PLAYING)
      {
        moveP1Paddle(2);
      }
      break;
    case 0x26:
      if(tableState == TABLE_PLAYING)
      {
        moveP2Paddle(2);
      }
      break;
    case 0x28:
      if(tableState == TABLE_PLAYING)
      {
        moveP2Paddle(-2);
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
    float32 timeStep = 1.0f / 60.0f;
    worldPtr->Step(timeStep, 6, 2);

    b2Vec2 p1PaddlePos = p1PaddleBody->GetPosition();
    PaddleDrawable *paddle = new PaddleDrawable(p1PaddlePos.x * pixelsPerUnit, p1PaddlePos.y * pixelsPerUnit, paddleWidth * pixelsPerUnit, paddleHeight * pixelsPerUnit);
    paddle->id = 1;
    paddle->color = 0xFFFFFF;
    render.updateMiddleground(paddle);
    
    b2Vec2 p2PaddlePos = p2PaddleBody->GetPosition();
    PaddleDrawable *paddle2 = new PaddleDrawable(p2PaddlePos.x * pixelsPerUnit, p2PaddlePos.y * pixelsPerUnit, paddleWidth * pixelsPerUnit, paddleHeight * pixelsPerUnit);
    paddle2->id = 2;
    paddle2->color = 0xFFFFFF;
    render.updateMiddleground(paddle2);
    
    b2Vec2 ballPos = ballBody->GetPosition();
    CircleDrawable *circle = new CircleDrawable(ballPos.x * pixelsPerUnit, ballPos.y * pixelsPerUnit, ballRadius * pixelsPerUnit);
    circle->id =3;
    circle->color = 0xFFFFFF;
    render.updateMiddleground(circle);

    float goalDistance = 0.5f;

    if(ballPos.x < goalDistance)
    {
      tableState = TABLE_DONE;
      p2Score += 1;
      
      char p2ScoreString[20];
      sprintf(p2ScoreString, "%d", p2Score);
      TextDrawable *p2ScoreText = new TextDrawable(p2ScoreString, 70.0f, 90.0f, false);
      p2ScoreText->id = 2000;
      p2ScoreText->SetColor(0xFFFFFF);
      p2ScoreText->SetSize(3);
      render.updateForeground(p2ScoreText);
    }

    if(ballPos.x > tableWidth - goalDistance)
    {
      tableState = TABLE_DONE;
      p1Score += 1;
     
      char p1ScoreString[20];
      sprintf(p1ScoreString, "%d", p1Score);
      TextDrawable *p1ScoreText = new TextDrawable(p1ScoreString, 30.0f, 90.0f, false);
      p1ScoreText->id = 2000;
      p1ScoreText->SetColor(0xFFFFFF);
      p1ScoreText->SetSize(3);
      render.updateForeground(p1ScoreText);
    }
  }
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
  b2Vec2 bodyPos = p1PaddleBody->GetPosition();
  float yPos = bodyPos.y + yDist;

  if(yPos > (tableHeight - 2))
  {
    yPos = (tableHeight - 2);
  }

  if(yPos < 2)
  {
    yPos = 2;
  }

  p1PaddleBody->SetTransform(b2Vec2(bodyPos.x, yPos), 0.0f);
  
  PaddleDrawable *paddle = new PaddleDrawable(bodyPos.x * pixelsPerUnit, yPos * pixelsPerUnit, paddleWidth * pixelsPerUnit, paddleHeight * pixelsPerUnit);
  paddle->id = 1;
  paddle->color = 0xFFFFFF;
  render.updateMiddleground(paddle);
}

void Table::moveP2Paddle(float yDist)
{
  b2Vec2 bodyPos = p2PaddleBody->GetPosition();
  float yPos = bodyPos.y + yDist;

  if(yPos > (tableHeight - 2))
  {
    yPos = (tableHeight - 2);
  }

  if(yPos < 2)
  {
    yPos = 2;
  }

  p2PaddleBody->SetTransform(b2Vec2(bodyPos.x, yPos), 0.0f);

  PaddleDrawable *paddle2 = new PaddleDrawable(bodyPos.x * pixelsPerUnit, yPos * pixelsPerUnit, paddleWidth * pixelsPerUnit, paddleHeight * pixelsPerUnit);
  paddle2->id = 2;
  paddle2->color = 0xFFFFFF;
  render.updateMiddleground(paddle2);
}
