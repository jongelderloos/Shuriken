#include "Vec2D.h"

Vec2D::Vec2D()
{
  x = 0;
  y = 0;
}

Vec2D::Vec2D(float xDir, float yDir)
{
  x = xDir;
  y = yDir;
}

Vec2D Vec2D::operator=(const Vec2D& other)
{
  (*this).x = other.x;
  (*this).y = other.y;
  
  return *this;
}
  