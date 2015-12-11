#include "Point2D.h"

Point2D::Point2D()
{
  x = 0;
  y = 0;
}

Point2D::Point2D(float x, float y)
{
  this->x = x;
  this->y = y;
}

Point2D Point2D:: operator=( const Point2D& other )
{
  this->x = other.x;
  this->y = other.y;

  return *this;
}
