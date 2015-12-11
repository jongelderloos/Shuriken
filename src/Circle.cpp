#include "Circle.h"

Circle::Circle()
{
  radius = 1;
}

Circle::Circle(float x, float y) : Shape2D(x, y)
{
  radius = 1;
}

Circle::Circle(float x, float y, float r) : Shape2D(x, y)
{
  radius = r;
}

Circle Circle::operator=( const Circle& other )
{
  (*this).radius = other.radius;
  (*this).center = other.center;
  
  return *this;
}
