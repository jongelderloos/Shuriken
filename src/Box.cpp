#include "Box.h"
#include <cmath>

Box::Box()
{
  p1.x = -0.5;
  p1.y = -0.5;
  p2.x = 0.5;
  p2.y = 0.5;
  pos.x = 0;
  pos.y = 0;
}

Box::Box(float x, float y) : Shape2D(x, y)
{
  p1.x = -0.5;
  p1.y = -0.5;
  p2.x = 0.5;
  p2.y = 0.5;
}

Box::Box(float x, float y, float height, float width) : Shape2D(x, y)
{
  p1.x = -(width/2);
  p1.y = -(height/2);
  p2.x = width/2;
  p2.y = height/2;
}

Box Box:: operator=(const Box& other)
{
  (*this).p1 = other.p1;
  (*this).p2 = other.p2;
  (*this).pos = other.pos;

  return *this;
}

bool Box::checkCollision(const Box& other)
{
  if(((abs(pos.x - other.pos.x) * 2) <  ((p2.x - p1.x) + (other.p2.x - other.p1.x))) &&
     ((abs(pos.y - other.pos.y) * 2) <  ((p2.y - p1.y) + (other.p2.y - other.p1.y))))
  {
    return true;
  }
  return false;
}
