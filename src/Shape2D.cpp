#include "Shape2D.h"

Shape2D::Shape2D()
{
  pos.x = 0;
  pos.y = 0;
}

Shape2D::Shape2D(float x, float y)
{
  pos.x = x;
  pos.y = y;
}

Shape2D Shape2D::operator=(const Shape2D& other)
{
    (*this).pos = other.pos;
    
    return *this;
}

bool Shape2D::checkCollision(Shape2D* other)
{
  return false;
}

bool Shape2D::checkCollision(Box* other)
{
  return false;
}

bool Shape2D::checkCollision(Circle* other)
{
  return false;
}
