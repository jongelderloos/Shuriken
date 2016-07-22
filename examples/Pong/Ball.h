#ifndef _BALL_H_
#define _BALL_H_

#include "PhysObj2D.h"

class Ball : public PhysObj2D
{
public:
  Ball();
  Ball(std::string n, Point2D p, Vec2D v, HitBox2D hB, float r = 1, bool move = false, bool collide = false, bool grav = false, float m = 0);
  void init(std::string name, Point2D pos, Vec2D vel, HitBox2D hB, float radius = 1, bool canMove = false, bool canCollide = false, bool feelsGravity = false, float mass = 0);
  float radius;
  Point2D pos;
};

#endif //_BALL_H_
