#include "CollisionData2D.h"

CollisionData2D::CollisionData2D()
{
  velocity.x = 0;
  velocity.y = 0;
  impulse.x = 0;
  impulse.y = 0;
  pos.x = 0;
  pos.y = 0;
}

CollisionData2D::CollisionData2D(Vec2D vel, Vec2D imp, Point2D p)
{
    velocity = vel;
    impulse = imp;
    pos = p;
}

bool CollisionData2D::operator==(const CollisionData2D& other)
{
  if(velocity.x != other.velocity.x)
  {
    return false;
  }

  return true;
}
