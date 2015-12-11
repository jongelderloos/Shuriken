#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "PhysObj2D.h"

class Paddle : public PhysObj2D
{
public:
  Paddle();
  Paddle(std::string n, Point2D p, Vec2D v, HitBox2D hB, float h = 1, float w = 1, bool move = false, bool collide = false, bool grav = false, float m = 0);
  float height;
  float width;
};

#endif //_PADDLE_H_
