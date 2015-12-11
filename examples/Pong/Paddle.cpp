#include "Paddle.h"

Paddle::Paddle()
{
  height = 1;
  width = 1;
}

Paddle::Paddle(std::string n, Point2D p, Vec2D v, HitBox2D hB, float h, float w, bool move, bool collide, bool grav, float m)
  : PhysObj2D(n, p, v, hB, move, collide, grav, m)
{
  height = h;
  width = w;
}


