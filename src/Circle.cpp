#include "Circle.h"
#include "Box.h"
#include <cmath>

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

Circle Circle::operator=(const Circle& other)
{
  (*this).radius = other.radius;
  (*this).center = other.center;
  
  return *this;
}

bool Circle::checkCollision(Shape2D* other)
{
  return  other->checkCollision(this);
}

bool Circle::checkCollision(Circle* other)
{
  float xDist = abs(pos.x - other->pos.x);
  float yDist = abs(pos.y - other->pos.y);

  float dist = sqrt(pow(xDist, 2) + pow(yDist, 2));

  if( dist <= (radius + other->radius))
  {
    return true;
  }

  return false;
}

bool Circle::checkCollision(Box* other)
{
  // Center of the circle is inside the box
  if(pos.x <= (other->pos.x + other->p2.x) && pos.x >= (other->pos.x + other->p1.x) && pos.y <= (other->pos.y + other->p2.y) && pos.y >= (other->pos.y + other->p1.y))
  {
    return true;
  }
  // Center of the circle is inside the X edges of the box
  else if(pos.x <= other->p2.x && pos.x >= other->p1.x)
  {
    // Center of the circle is no more than its radius away from the edge of the box in the y coordinate
    if((pos.y + radius >= other->p1.y && pos.y < other->p1.y) || (pos.y - radius <= other->p2.y && pos.y > other->p2.y))
    {
      return true;
    }
  }
  // Center of the circle is inside the Y edges of the box
  else if(pos.y <= other->p2.y && pos.y >= other->p1.y)
  {
    // Center of the circle is no more than its radius away from the edge of the box in the x coordinate
    if((pos.x + radius >= other->p1.x && pos.x < other->p1.x) || (pos.x - radius <= other->p2.x && pos.x > other->p2.x))
    {
      return true;
    }
  }
  // Center of the circle is to the upper left of the box
  else if(pos.y > other->p2.y && pos.x < other->p1.x)
  {
    // Caclulate the distance between the center of the circle and corner of the box
    float xDist = abs(pos.x - other->p1.x);
    float yDist = abs(pos.y - other->p2.y);

    float dist = sqrt(pow(xDist, 2) + pow(yDist, 2));

    // Distance is less than radius
    if(dist <= radius)
    {
      return true;
    }
  }
  // Center of the circle is to the upper right of the box
  else if(pos.y > other->p2.y && pos.x > other->p2.x)
  {
    // Caclulate the distance between the center of the circle and corner of the box
    float xDist = abs(pos.x - other->p2.x);
    float yDist = abs(pos.y - other->p2.y);

    float dist = sqrt(pow(xDist, 2) + pow(yDist, 2));

    // Distance is less than radius
    if(dist <= radius)
    {
      return true;
    }
  }
  // Center of the circle is to the lower left of the box
  else if(pos.y < other->p1.y && pos.x < other->p1.x)
  {
    // Caclulate the distance between the center of the circle and corner of the box
    float xDist = abs(pos.x - other->p1.x);
    float yDist = abs(pos.y - other->p1.y);

    float dist = sqrt(pow(xDist, 2) + pow(yDist, 2));

    // Distance is less than radius
    if(dist <= radius)
    {
      return true;
    }
  }
  // Center of the circle is to the lower right of the box
  else if(pos.y < other->p1.y && pos.x > other->p2.x)
  {
    // Caclulate the distance between the center of the circle and corner of the box
    float xDist = abs(pos.x - other->p2.x);
    float yDist = abs(pos.y - other->p1.y);

    float dist = sqrt(pow(xDist, 2) + pow(yDist, 2));

    // Distance is less than radius
    if(dist <= radius)
    {
      return true;
    }
  }
  return false;
}
