#ifndef TABLE_H_
#define TABLE_H_

#include "game.h"
#include "ball.h"
#include "paddle.h"
#include "PhysSpace2D.h"
#include "Render2D.h"
#include "Box2D.h"

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
  void setVideoMemory(void* memoryPtr, int width, int height);

private:
  void moveP1Paddle(float);
  void moveP2Paddle(float);
  int p1Score;
  int p2Score;
  TABLE_STATE tableState;
  void* videoMemPtr;
  int windowWidth;
  int windowHeight;
  Render2D render;
  b2Body* bottomBody;
  b2Body* topBody;
  b2Body* p1PaddleBody;
  b2Body* p2PaddleBody;
  b2Body* ballBody;
  b2World* worldPtr;
  unsigned int msProcessTime;
  float tableHeight;
  float tableWidth;
  float paddleWidth;
  float paddleHeight;
  float ballRadius;
  float wallWidth;
  float pixelsPerUnit;
};

#endif // TABLE_H_
