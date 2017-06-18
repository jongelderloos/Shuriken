#include "Table.h"
#include "stdio.h"
#include "Windows.h"
#include "Box.h"
#include "Circle.h"
#include <string>
#include "SquareDrawable.h"
#include "CircleDrawable.h"
#include "TextDrawable.h"

//TODO: Add starting velocity based on paddle position
//TODO: Change ball velocity based on position of the paddle it hits
//TODO: Move paddleDrawable to box drawable...
//TODO: fix rendering so the ball does no show on the other side of screen after scoring

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
  ballOnLeft = true;
  ballVelDirection = 1;
  bounceCount = 1;

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

  reset();

  p1Score = 0;
  p2Score = 0;

  msProcessTime = (1.0f / 60.0f) * 1000.0f;

  SquareDrawable *background = new SquareDrawable((tableWidth / 2), (tableHeight / 2), tableWidth, tableHeight);
  background->id = 1000;
  background->color = 0x0;
  render.addToBackground(background);

  b2Vec2 p1PaddlePos = p1PaddleBody->GetPosition();
  SquareDrawable *paddle = new SquareDrawable(p1PaddlePos.x, p1PaddlePos.y, paddleWidth, paddleHeight);
  paddle->id = 1;
  paddle->color = 0xFFFFFF;
  render.addToMiddleground(paddle);

  b2Vec2 p2PaddlePos = p2PaddleBody->GetPosition();
  SquareDrawable *paddle2 = new SquareDrawable(p2PaddlePos.x, p2PaddlePos.y, paddleWidth, paddleHeight);
  paddle2->id = 2;
  paddle2->color = 0xFFFFFF;
  render.addToMiddleground(paddle2);

  b2Vec2 ballPos = ballBody->GetPosition();
  CircleDrawable *circle = new CircleDrawable(ballPos.x, ballPos.y, ballRadius);
  circle->id = 3;
  circle->color = 0xFFFFFF;
  render.addToMiddleground(circle);

  b2Vec2 topWallPos = topBody->GetPosition();
  SquareDrawable *top = new SquareDrawable(topWallPos.x, topWallPos.y, tableWidth, wallWidth);
  top->id = 4;
  top->color = 0xFFFFFF;
  render.addToMiddleground(top);

  b2Vec2 botWallPos = bottomBody->GetPosition();
  SquareDrawable *bot = new SquareDrawable(botWallPos.x, botWallPos.y, tableWidth, wallWidth);
  bot->id = 5;
  bot->color = 0xFFFFFF;
  render.addToMiddleground(bot);

  // Draw the dotted line

  for(int i = 0; i < 40; i++)
  {
    if(i % 2 == 0)
    {
      SquareDrawable *dot = new SquareDrawable(30.0f, (i + 1), 0.3f, 1.0f);
      dot->id = 6000 + i;
      dot->color = 0xFFFFFF;
      render.addToMiddleground(dot);
    }
  }

  char p1ScoreString[20];
  sprintf(p1ScoreString, "%d", p1Score);
  TextDrawable *p1ScoreText = new TextDrawable(p1ScoreString, 18.0f, 36.0f, false);
  p1ScoreText->id = 2001;
  p1ScoreText->SetColor(0xFFFFFF);
  p1ScoreText->SetSize(3);
  render.addToForeground(p1ScoreText);

  char p2ScoreString[20];
  sprintf(p2ScoreString, "%d", p2Score);
  TextDrawable *p2ScoreText = new TextDrawable(p2ScoreString, 42.0f, 36.0f, false);
  p2ScoreText->id = 2002;
  p2ScoreText->SetColor(0xFFFFFF);
  p2ScoreText->SetSize(3);
  render.addToForeground(p2ScoreText);
}

Table::~Table()
{
}

void Table::reset()
{
  p1PaddleBody->SetTransform(b2Vec2(1.0f, 20.0f), 0.0f);
  p2PaddleBody->SetTransform(b2Vec2(59.0f, 20.0f), 0.0f);

  float ballXVel;
  float ballX;
  float ballY = 20.0f;

  if(ballOnLeft)
  {
    ballX = 3.0f;
    ballXVel = 15.0f;
  }
  else
  {
    ballX = 57.0f;
    ballXVel = -15.0f;
  }
  ballBody->SetTransform(b2Vec2(ballX,ballY), 0.0f);
  ballBody->SetLinearVelocity(b2Vec2(ballXVel, 2.0f));
}

void Table::setVideoMemory(void* memoryPtr, int width, int height)
{
  render.setWindowSize(width, height);
  render.setScreenBuffer(memoryPtr);
  render.setPixelsPerUnit(pixelsPerUnit);
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
      if(tableState == TABLE_START)
      {
        tableState = TABLE_PLAYING;
      }
      else if(tableState == TABLE_DONE)
      {
        reset();
        tableState = TABLE_START;
      }
      break;
    case 0x53:
    case 0x73: // s
      if(tableState == TABLE_PLAYING || tableState == TABLE_START)
      {
        moveP1Paddle(-2);

        if(tableState == TABLE_START)
        {
          moveBall(-2);
        }
      }
      break;
    case 0x57:
    case 0x77: // w
      if(tableState == TABLE_PLAYING || tableState == TABLE_START)
      {
        moveP1Paddle(2);

        if(tableState == TABLE_START)
        {
          moveBall(2);
        }
      }
      break;
    case 0x26:
      if(tableState == TABLE_PLAYING || tableState == TABLE_START)
      {
        moveP2Paddle(2);

        if(tableState == TABLE_START)
        {
          moveBall(2);
        }
      }
      break;
    case 0x28:
      if(tableState == TABLE_PLAYING || tableState == TABLE_START)
      {
        moveP2Paddle(-2);

        if(tableState == TABLE_START)
        {
          moveBall(-2);
        }
      }
      break;
    default:
      break;
  }
}

void Table::update(void)
{
  b2Vec2 ballPos = ballBody->GetPosition();

  if(tableState == TABLE_PLAYING)
  {
    float32 timeStep = 1.0f / 60.0f;
    worldPtr->Step(timeStep, 6, 2);

    bool bounceOccured = false;

    if(ballVelDirection > 0 && ballBody->GetLinearVelocity().x < 0.0f)
    {
      ballVelDirection = -1;
      bounceCount++;
      bounceOccured = true;
    }
    else if(ballVelDirection < 0 && ballBody->GetLinearVelocity().x > 0.0f)
    {
      ballVelDirection = 1;
      bounceCount++;
      bounceOccured = true;
    }

    if(bounceCount % 3 == 0 && bounceOccured)
    {
      b2Vec2 vel = ballBody->GetLinearVelocity();

      vel.x = vel.x * 1.3f;
      vel.y = vel.y * 1.3f;
      ballBody->SetLinearVelocity(vel);
    }

    float goalDistance = 0.75f;

    if(ballPos.x > tableWidth - goalDistance)
    {
      tableState = TABLE_DONE;
      p1Score += 1;
      ballOnLeft = false;
     
      char p1ScoreString[20];
      sprintf(p1ScoreString, "%d", p1Score);
      TextDrawable *p1ScoreText = new TextDrawable(p1ScoreString, 18.0f, 36.0f, false);
      p1ScoreText->id = 2001;
      p1ScoreText->SetColor(0xFFFFFF);
      p1ScoreText->SetSize(3);
      render.updateForeground(p1ScoreText);
    }
    
    if(ballPos.x < goalDistance)
    {
      tableState = TABLE_DONE;
      p2Score += 1;
      ballOnLeft = true;
      
      char p2ScoreString[20];
      sprintf(p2ScoreString, "%d", p2Score);
      TextDrawable *p2ScoreText = new TextDrawable(p2ScoreString, 42.0f, 36.0f, false);
      p2ScoreText->id = 2002;
      p2ScoreText->SetColor(0xFFFFFF);
      p2ScoreText->SetSize(3);
      render.updateForeground(p2ScoreText);
    }
  }

  b2Vec2 p1PaddlePos = p1PaddleBody->GetPosition();
  SquareDrawable *paddle = new SquareDrawable(p1PaddlePos.x, p1PaddlePos.y, paddleWidth, paddleHeight);
  paddle->id = 1;
  paddle->color = 0xFFFFFF;
  render.updateMiddleground(paddle);
  
  b2Vec2 p2PaddlePos = p2PaddleBody->GetPosition();
  SquareDrawable *paddle2 = new SquareDrawable(p2PaddlePos.x, p2PaddlePos.y, paddleWidth, paddleHeight);
  paddle2->id = 2;
  paddle2->color = 0xFFFFFF;
  render.updateMiddleground(paddle2);
  
  CircleDrawable *circle = new CircleDrawable(ballPos.x, ballPos.y, ballRadius);
  circle->id = 3;
  circle->color = 0xFFFFFF;
  render.updateMiddleground(circle);
    
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
  
  SquareDrawable *paddle = new SquareDrawable(bodyPos.x, yPos, paddleWidth, paddleHeight);
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

  SquareDrawable *paddle2 = new SquareDrawable(bodyPos.x, yPos, paddleWidth, paddleHeight);
  paddle2->id = 2;
  paddle2->color = 0xFFFFFF;
  render.updateMiddleground(paddle2);
}

void Table::moveBall(float yDist)
{
  b2Vec2 bodyPos = ballBody->GetPosition();
  float yPos = bodyPos.y + yDist;

  if(yPos > (tableHeight - 2))
  {
    yPos = (tableHeight - 2);
  }

  if(yPos < 2)
  {
    yPos = 2;
  }

  ballBody->SetTransform(b2Vec2(bodyPos.x, yPos), 0.0f);
  
  CircleDrawable *ball = new CircleDrawable(bodyPos.x, yPos, ballRadius);
  ball->id = 3;
  ball->color = 0xFFFFFF;
  render.updateMiddleground(ball);
}


