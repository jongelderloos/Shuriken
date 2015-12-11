#ifndef _BALL_H_
#define _BALL_H_

#include "PhysObj2D.h"

class Ball : public PhysObj2D
{
public:
  Ball();
  Ball(std::string n, Point2D p, Vec2D v, HitBox2D hB, float r = 1, bool move = false, bool collide = false, bool grav = false, float m = 0);
  void init(std::string n, Point2D p, Vec2D v, HitBox2D hB, float r = 1, bool move = false, bool collide = false, bool grav = false, float m = 0) override;
  float radius;
  Point2D pos;
};

#endif //_BALL_H_
