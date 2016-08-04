#include "Box.h"
#include "Circle.h"
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

bool Box::checkCollision(Shape2D* other)
{
  return  other->checkCollision(this);
}

bool Box::checkCollision(Box* other)
{
  if(((abs(pos.x - other->pos.x) * 2) <  ((p2.x - p1.x) + (other->p2.x - other->p1.x))) &&
     ((abs(pos.y - other->pos.y) * 2) <  ((p2.y - p1.y) + (other->p2.y - other->p1.y))))
  {
    return true;
  }
  return false;
}

bool Box::checkCollision(Circle* other)
{
  // Center of the circle is inside the box
  if(other->pos.x <= (pos.x + p2.x) && other->pos.x >= (pos.x + p1.x) && other->pos.y <= (pos.y + p2.y) && other->pos.y >= (pos.y + p1.y))
  {
    return true;
  }
  // Center of the circle is inside the X edges of the box
  else if(other->pos.x <= pos.x + p2.x && other->pos.x >= pos.x + p1.x)
  {
    // Center of the circle is no more than its radius away from the edge of the box in the y coordinate
    if((other->pos.y + other->radius >= pos.y + p1.y && other->pos.y < pos.y + p1.y) || (other->pos.y - other->radius <= pos.y + p2.y && other->pos.y > pos.y + p2.y))
    {
      return true;
    }
  }
  // Center of the circle is inside the Y edges of the box
  else if(other->pos.y <= pos.y + p2.y && other->pos.y >= pos.y + p1.y)
  {
    // Center of the circle is no more than its radius away from the edge of the box in the x coordinate
    if((other->pos.x + other->radius >= pos.x + p1.x && other->pos.x < pos.x + p1.x) || (other->pos.x - other->radius <= pos.x + p2.x && other->pos.x > pos.x + p2.x))
    {
      return true;
    }
  }
  // Center of the circle is to the upper left of the box
  else if(other->pos.y > pos.y + p2.y && other->pos.x < pos.x + p1.x)
  {
    // Caclulate the distance between the center of the circle and corner of the box
    float xDist = abs(other->pos.x - pos.x + p1.x);
    float yDist = abs(other->pos.y - pos.y + p2.y);

    float dist = sqrt(pow(xDist, 2) + pow(yDist, 2));

    // Distance is less than radius
    if(dist <= other->radius)
    {
      return true;
    }
  }
  // Center of the circle is to the upper right of the box
  else if(other->pos.y > pos.y + p2.y && other->pos.x > pos.x + p2.x)
  {
    // Caclulate the distance between the center of the circle and corner of the box
    float xDist = abs(other->pos.x - pos.x + p2.x);
    float yDist = abs(other->pos.y - pos.y + p2.y);

    float dist = sqrt(pow(xDist, 2) + pow(yDist, 2));

    // Distance is less than radius
    if(dist <= other->radius)
    {
      return true;
    }
  }
  // Center of the circle is to the lower left of the box
  else if(other->pos.y < pos.y + p1.y && other->pos.x < pos.x + p1.x)
  {
    // Caclulate the distance between the center of the circle and corner of the box
    float xDist = abs(other->pos.x - pos.x + p1.x);
    float yDist = abs(other->pos.y - pos.y + p1.y);

    float dist = sqrt(pow(xDist, 2) + pow(yDist, 2));

    // Distance is less than radius
    if(dist <= other->radius)
    {
      return true;
    }
  }
  // Center of the circle is to the lower right of the box
  else if(other->pos.y < pos.y + p1.y && other->pos.x > pos.x + p2.x)
  {
    // Caclulate the distance between the center of the circle and corner of the box
    float xDist = abs(other->pos.x - pos.x + p2.x);
    float yDist = abs(other->pos.y - pos.y + p1.y);

    float dist = sqrt(pow(xDist, 2) + pow(yDist, 2));

    // Distance is less than radius
    if(dist <= other->radius)
    {
      return true;
    }
  }
  return false;
}
