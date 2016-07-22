#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "PhysObj2D.h"

class Paddle : public PhysObj2D
{
public:
  Paddle();
  Paddle(std::string n, Point2D p, Vec2D v, HitBox2D hB, float h = 1, float w = 1, bool move = false, bool collide = false, bool grav = false, float m = 0);
  void init(std::string name, Point2D pos, Vec2D vel, HitBox2D hitBox, float height = 1, float width = 1, bool canMove = false, bool canCollide = false, bool fellsGravity = false, float mass = 0);
  float height;
  float width;
};

#endif //_PADDLE_H_
