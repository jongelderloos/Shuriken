#include "Ball.h"

Ball::Ball()
{
  radius = 1;
}

Ball::Ball(std::string n, Point2D p, Vec2D v, HitBox2D hB, float r, bool move, bool collide, bool grav, float m)
{
  init(n, p, v, hB, r, move, collide, grav, m);
}

void Ball::init(std::string name, Point2D pos, Vec2D vel, HitBox2D hitBox, float radius, bool canMove, bool canCollide, bool feelsGravity, float mass)
{
  this->name = name;
  this->pos = pos;
  this->vel = vel;
  this->hitBox = hitBox;
  this->radius = radius;
  this->canMove = canMove;
  this->canCollide = canCollide;
  this->feelsGravity = feelsGravity;
  this->mass = mass;
}
