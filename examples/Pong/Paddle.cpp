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

void Paddle::init(std::string name, Point2D pos, Vec2D vel, HitBox2D hitBox, float height, float width, bool canMove, bool canCollide, bool feelsGravity, float mass)
{
  this->name = name;
  this->pos = pos;
  this->vel = vel;
  this->hitBox = hitBox;
  this->height = height;
  this->width = width;
  this->canMove = canMove;
  this->canCollide = canCollide;
  this->feelsGravity = feelsGravity;
  this->mass = mass;

}


