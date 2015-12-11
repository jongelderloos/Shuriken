#include "Ball.h"

Ball::Ball()
{
  radius = 1;
}

Ball::Ball(std::string n, Point2D p, Vec2D v, HitBox2D hB, float r, bool move, bool collide, bool grav, float m)
{
  init(n, p, v, hB, r, move, collide, grav, m);
}

void Ball::init(std::string n, Point2D p, Vec2D v, HitBox2D hB, float r, bool move, bool collide, bool grav, float m)
  :PhysObj2D(n, p, v, hB, move, collide, grav, m)
{
  radius = r;
}
